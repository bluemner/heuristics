#ifndef _betacore_dijkstra_hpp_
#define _betacore_dijkstra_hpp_

namespace{
	template<typename I>
	class Node{
		private:
		I id;//64 bit
		public:
			Node(I id,std::string name){
				this->id = id;
				this->name = 
			}
	};
	template<typename T>
	class Edge{
		private:
		I * source;
		I * target;
		T cost;
		public:
			Edge(Node &source,Node &target, T cost){
				this->source = source;
				this->target = target;
				this->cost = cost;
			}
	};
	
	/*
	 *
	 */
	template<typename N, typename E>
	class Graph{
		std::vector<N> nodes;
		std::vector<E> edges;

		public:
			void successor(Node &node, Node &result){
				//gets node;
			}
	};

	// C is cost datatype 
	template<typename C>
	class Dijkstra{

		private:
		std::priority_queue<Node> frontier;
		std::std
		std::set<Node> explored;

		public:
			dijkstra(){
			}
			
			~dijkstra(){

			}

			/**
			 * returns zero on sucess
			 */
			int run ( Graph &graph, Node &source, Node &goal, std::vector<Edges> &path ){
				Node n;
				C cost = (C) 0;
				
				if( frontier.empty() ){
					return -1;
				}

				n = frontier.top();
				frontier.pop();

				explored.insert(n);
				std::vector<Node> succssor;
				// Get sucessor
				Graph.getSucesssor(n, succssor);

				for ( auto s : succssor) {
					if( frontier.){

					}
				}



			}
	};
}
#endif