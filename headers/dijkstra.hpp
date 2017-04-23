/** MIT License

	Copyright (c) 2017 Brandon Bluemner

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
 */
#ifndef _betacore_dijkstra_hpp_
#define _betacore_dijkstra_hpp_

#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <functional>
#include <limits>
#include <thread>
#include "./node.hpp"
#include "./edge.hpp"
#include "./graph.hpp"
#include <functional>

namespace betacore{
	//Errors
	struct Dijkstra_Exception : public std::exception {
		const char * what () const throw () {
			return "Dijkstra Exception";
		}
	};
	// Define our queue
	template<typename T, typename I>
	class dijkstra_priority_queue{
		public:
			//std::vector<I> path;
			T cost;
			bool operator > (const dijkstra_priority_queue& right_hand_side){
				return cost > right_hand_side.cost;
			}
	};
	// Define our queue comparator
	template<typename T, typename I>
	class comparator{
		public:
			bool operator()(dijkstra_priority_queue<T,I> a, dijkstra_priority_queue<T,I> b)const
			{
				return (a > b);
			}
	};
	template<typename T, typename I>
	class Order	{
		public:
		bool operator()(std::pair<T,I> const& a, std::pair<T,I> const& b) const
		{
			
			return (a.first == b.first)? a.second < b.second : a.first > b.first;
		}
	};
	//implement Dijkstra algorithm
	template<typename T, typename I>
	class Dijkstra{
		private:			
			std::priority_queue<std::pair<T,I>,std::vector<std::pair<T,I>>, Order<T,I> > frontier; // keeps track of priority std::greater<std::pair<T,I>>
			std::set<I> current; // keeps track of frontier
			std::set<I> explored; // explored nodes
			std::map<I,T> g;
			std::map<I,I> _path;
			std::function<T( I u, I ui)> cost;

			void do_successor(I u, I ui,T cst, T _cost){
						// ui not in E and ui not in f
						T new_cost = cst;//cost(u,ui);
						bool ex = explored.find(ui) != explored.end() ;
						bool front = current.find(ui) != current.end();
						if( !ex && !front )
						{
								g[ui]= g[u] +new_cost ;														
								frontier.push(std::make_pair(g[ui],ui));
								current.insert(ui);
								_path[ui]=u;							
						}
						// ui in F
						else if(front){
							if( g[u] + new_cost < g[ui] ){
								g[ui] = g[u] +new_cost;
								_path[ui] = u;
							// /	std::cout<<"+adding edge:"<<u <<" cost:"<< g[ui]<<"\n"; 
							}else if(g[u] + new_cost == g[ui]){
								_path[ui] = u;
							}
						}
						// ui in E
						else if(ex)
						{
							if( g[u] + new_cost < g[ui] ){
								//std::cout<<"!adding edge:"<<u <<" cost:"<< g[ui]<<"\n";
								explored.erase(explored.find(ui));						
								frontier.push(std::make_pair(g[ui],ui));
								current.insert(u);
							//std::cout<<"!adding edge:"<<u <<" cost:"<< g[ui]<<"\n"; 
							}
						}else{
							std::cerr<< "bug"<<"\n";
						}
			}
			void join_all(std::vector<std::thread>& v)
			{
				for (std::vector<std::thread>::iterator it = v.begin() ; it != v.end(); ++it){
					it->join();
				}
			}
		public:
			Dijkstra(){
			}
			~Dijkstra(){
			}
			//
			// Graph<T,I> &graph
			// I &goal
			//
			void run (
				I source,
				I goal,
				std::map<I,I> &path,
				std::function<T( I u, I ui)> &cost,
				std::function<void(I &node, std::vector<Edge<T,I>> &result)> &Succ
			 )
			 {
				this->cost = cost;
				
				I u;				
				T _cost = (T) std::numeric_limits<T>::max();
				frontier.push(std::make_pair(0,source));
				current.insert(source);
				//std::map<I,T> g;
				
				g[source] =(T) cost(source,source);
				while(!frontier.empty()){
					if( frontier.empty() ){
						std::cerr<<"The fronter is empty, how can this be?"<<"\n";;
						throw Dijkstra_Exception();
					}
					u = std::get<1>(frontier.top()); // get next node
					std::cout<<"Node U::"<< u<<"\n";
						frontier.pop(); // move remove the next from the que

					if(current.find(u)!= current.end())
						current.erase(current.find(u));
					//if u is the goal is it has a smaller cost
					if( u == goal && g[goal]< _cost)
					{
						std::cout<< "Goal Found" <<"\n";
						_cost = g[goal];
					}
					// this stop exploration
					if(_cost< g[u]){
						break;
					}				

					if(g.find(u) == g.end()){
						std::cerr<<"The weight is unkown, how can this be?"<<"\n";;
						throw Dijkstra_Exception();
					}

					explored.insert(u);
					std::vector<Edge<T,I>> successor;

					// Get successor
					//graph.successor(u, successor);
					Succ(u,successor);
					for ( auto s : successor ) {
						I ui = s.get_target();//.get_id();
						// ui not in E and ui not in f
						if(explored.find(ui) == explored.end() && current.find(ui) == current.end())
						{
								g[ui]= g[u] + cost(u,ui);
								if(g[ui]> _cost){ // if we have our goal then we see if any paths can be added 
									continue;
								}
								//frontier.push(ui);
								frontier.push(std::make_pair(g[ui],ui));
								current.insert(ui);
								path[ui]=u;
								std::cout<<"Adding to frontier edge:"<<ui <<" cost:"<< g[ui]<<"\n";
							
						}
						// ui in F
						else if(current.find(ui) != current.end()){
							if( g[u] + cost(u,ui) < g[ui] ){
								g[ui] = g[u] + cost(u,ui);
								path[ui] = u;
								std::cout<<"+adding edge:"<<u <<" cost:"<< g[ui]<<"\n"; 
							}
						}
						// ui in E
						else if(explored.find(ui) != explored.end())
						{
							if( g[u] + cost(u,ui) < g[ui] ){
								explored.erase(explored.find(ui));
								//frontier.push(ui);
								frontier.push(std::make_pair(g[ui],ui));
								current.insert(source);
							std::cout<<"!adding edge:"<<u <<" cost:"<< g[ui]<<"\n"; 
							}
						}else{
							std::cerr<< "bug"<<"\n";
						}
					}
				}//while(true);

				for(auto e: explored){
					std::cout<< "explored node:"<< e <<"\n";
				}
				for(auto c: current){
						std::cout<< "frontier node:"<< c <<"\n";
				}
				u = goal;
				I mp = path[u];
				std::cout<< u <<"<-";
				while (mp !=source){
					if(!path.count(mp)){
						std::cerr<<"Path from sink doesn't lead back to source" <<"\n";
						throw Dijkstra_Exception();
					}
					std::cout<< mp <<"<-";
					mp = path[mp];
				}
				std::cout<< source << "\n";
			}
			
			//
			// Graph<T,I> &graph
			// I &goal
			//
			void run (
				I source,
				std::vector<I> &goal_v,
				std::map<I,I> &path,
				std::function<T( I u, I ui)> &cost,
				std::function<void(I &node, std::vector<Edge<T,I>> &result)> &Succ
			 )
			 {
				this->cost = cost;
				
				I u;
				I ui;
				T _cost = (T) std::numeric_limits<T>::max();
			
				current.insert(source);
				
				g[source] =(T) cost(source,source);
				frontier.push(std::make_pair(g[source],source));
				I _goal = goal_v.at(0);
				bool quit = false;
				while(!frontier.empty()){
					u = std::get<1>(frontier.top());
					frontier.pop(); 
					
					if(current.find(u)!= current.end())
						current.erase(current.find(u));
					//if u is the goal is it has a smaller cost
					if(goal_v.size() > 1)
					for(auto goal : goal_v){
						if( u == goal && g[goal]< _cost)
						{
						//	std::cout<< "Min Goal Found:"<< goal <<"\tcost:" << g[goal] <<"\n";
							_cost = g[goal];
							_goal = goal;
							quit = true;
						}
						else{
						//	std::cout<< "Other Goal Found:"<< goal <<"\tcost:" << g[goal] <<"\n";
						}
					}

					//this stop exploration (if positive only)
					if( u == _goal || _cost< g[u] || quit){
						break;
					}


					// if(g.find(u) == g.end()){
					// 	std::cerr<<"The weight is unkown, how can this be?"<<"\n";;
					// 	throw Dijkstra_Exception();
					// }

					explored.insert(u);
					std::vector<Edge<T,I>> successor;

					// Get successor
					//graph.successor(u, successor);
					Succ(u,successor);
					std::vector<std::thread> thread_list;
					for ( auto s : successor ) {
						ui = s.get_target();					
						do_successor(u,ui,s.get_cost() ,_cost);
						// try{
						// 	thread_list.push_back(std::thread(&betacore::Dijkstra<T,I>::do_successor,this,u,ui,s.get_cost(),_cost)); //,std::ref(path)
						// }catch(const std::exception& e){
						// 		std::cerr<<"Problem with thread" <<std::endl;
						// }
					}
					join_all(thread_list);
					//path = this->_path;
					if(frontier.empty()) std::cout<< "out of nodes" <<std::endl;
				}//while(true);
				std::cout<< "explored node count:"<< explored.size() <<"\n";
				std::cout<<"cost:"<< g[_goal] <<"\n";
			
				path= _path;
			}

			
	};
}
#endif