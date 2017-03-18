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

#include "./node.hpp"
#include "./edge.hpp"
#include "./graph.hpp"

namespace betacore{
	struct Dijkstra_Exception : public std::exception {
		const char * what () const throw () {
			return "Dijkstra Exception";
		}
	};

	template<typename T, typename I>
	class Dijkstra{
		private:
			std::priority_queue<I> frontier;
			std::set<I> current;
			std::set<I> explored;

		public:
			Dijkstra(){
			}

			~Dijkstra(){
			}

			void run ( Graph<T,I> &graph, I &source, I &goal, std::vector<Edge<T,I>> &path ){
				I n;
				T cost = (T) 0;
				frontier.push(source);
				if( frontier.empty() ){
					throw Dijkstra_Exception();
				}
				while( frontier.size() > 0 ){
					n = frontier.top();
					frontier.pop();
					explored.insert(n);
					std::vector<I> successor;
					// Get successor
					graph.successor(n, successor);
					for ( auto s : successor ) {
						
					}
				}
			}
	};
}
#endif