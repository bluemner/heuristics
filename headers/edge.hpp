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
			bool operator==(const Edge<T,I> &rhs){
				return (this->source == rhs.source &&
					this->target == rhs.target&&
				this->cost == rhs.cost
				);
			}
	};
}
#endif