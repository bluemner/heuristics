#ifndef _betacore_edge_hpp_
#define _betacore_edge_hpp_
#include "../headers/node.hpp"
namespace betacore{
	template<typename T, typename I>
	class Edge{
		private:
			I id;
			I source;
			I target;
			T cost;
		public:
			Edge(){}
			Edge(I &source, I &target, T &cost){
				this->source = source;
				this->target = target;
				this->cost = cost;
			}

			I get_source(){
				return this->source;
			}
			I get_target(){
				return this->target;
			}
			T get_cost(){
				return this->cost;
			}
	};
}
#endif