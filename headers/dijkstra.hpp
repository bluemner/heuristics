#ifndef _betacore_dijkstra_hpp_
#define _betacore_dijkstra_hpp_
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
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
			std::vector<I> path;
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
			std::priority_queue<dijkstra_priority_queue<T,I>,std::vector<dijkstra_priority_queue<T,I>>, comparator<T,I>> frontier; // keeps track of priority 
			std::set<I> current; // keeps track of frontier
			std::set<I> explored; // explored nodes

		public:
			Dijkstra(){
			}

			~Dijkstra(){
			}
			//
			// Graph<T,I> &graph 
			// I &goal
			// 
			void run (Graph<T,I> &graph , I &source, I &goal, std::vector<Edge<T,I>> &path, std::map<I,T> &g){
				I n;
				T cost = (T) 0;
				frontier.push(source);
				current.push_back(source);
				
				g[source] =(T) 0;
				do{
				
					if( frontier.empty() ){
						throw Dijkstra_Exception();
					}

					n = frontier.top();//get next node
						frontier.pop();//move remove the next from the que

					if( n == goal )
					{
						break;
					}

					explored.insert(n);
					std::vector<Edge<T,I>> successor;
					// Get successor
					graph.successor(n, successor);
					for ( auto s : successor ) {
						if(explored.find(s) == explored.end() && current.find(s) == current.end()){
							 frontier.push_back(s)
						}
					}

				}while(true);
			}
	};
}
#endif