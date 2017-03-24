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
#include "./node.hpp"
#include "./edge.hpp"
#include "./graph.hpp"


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
	//implement Dijkstra algorithm
	template<typename T, typename I>
	class Dijkstra{
		private:
			//std::priority_queue<dijkstra_priority_queue<T,I>,std::vector<dijkstra_priority_queue<T,I>>, comparator<T,I>> frontier; // keeps track of priority
			std::priority_queue<I,std::vector<I>, std::less<I> > frontier; // keeps track of priority
			std::set<I> current; // keeps track of frontier
			std::set<I> explored; // explored nodes
			T cost();
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
				I u;
				//T cost = (T) 0;
				frontier.push(source);
				current.insert(source);
				std::map<I,T> g;
				g[source] =(T) 0;
				do{
					if( frontier.empty() ){
						std::cerr<<"The fronter is empty, how can this be?";
						throw Dijkstra_Exception();
					}
					u = frontier.top(); // get next node
						frontier.pop(); // move remove the next from the que
					if( u == goal )
					{

						break;
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
							frontier.push(ui);
							current.insert(source);
							path[ui]=u;
						}
						// ui in F
						else if(current.find(ui) != current.end()){
							if( g[u] + cost(u,ui) < g[ui] ){
								g[ui] = g[u] + cost(u,ui);
								path[ui] = u;
							}
						}
						// ui in E
						else if(explored.find(ui) != explored.end())
						{
							if( g[u] + cost(u,ui) < g[ui] ){
								explored.erase(explored.find(ui));
								frontier.push(ui);
								current.insert(source);
							}
						}
					}
				}while(true);

				I mp = path[u];
				while (mp !=source){
					if(!path.count(mp)){
						std::cerr<<"Path from sink doesn't lead back to source";
						throw Dijkstra_Exception();
					}
					mp = path[mp];
				}

			}
	};
}
#endif