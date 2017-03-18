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
	template<typename T, typename I>
	class Dijkstra{

		private:
		std::priority_queue<Node<I>> frontier;
		std::set<Node<I>> explored;

		public:
			Dijkstra(){
			}

			~Dijkstra(){

			}

			// /**
			//  * returns zero on sucess
			//  */
			// int run ( Graph<T,I> &graph, Node<I> &source, Node<I> &goal, std::vector<Edges<T,I>> &path ){
			// 	Node n;
			// 	C cost = (C) 0;

			// 	if( frontier.empty() ){
			// 		return -1;
			// 	}

			// 	n = frontier.top();
			// 	frontier.pop();

			// 	explored.insert(n);
			// 	std::vector<Node> successor;
			// 	// Get successor
			// 	Graph.successor(n, successor);

			// 	for ( auto s : successor) {
			// 		if( false){

			// 		}
			// 	}
			// 	return -1;


			// }
	};
}
#endif