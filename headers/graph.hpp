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
#ifndef _betacore_graph_hpp_
#define _betacore_graph_hpp_
#include "./node.hpp"
#include "./edge.hpp"
#include <vector>
#include <iostream>
namespace betacore{
	template<typename T, typename I>
	class Graph{
		private:
			std::vector<betacore::Node<I>> nodes;
			std::vector<betacore::Edge<T,I>> edges;
			betacore::Node<I> * source;
			std::vector<I> targets;
			I next_id;
			void parse_line(std::string &line){
				std::stringstream sstream(line);
				std::string item;
				char type = 0;
				std::vector<std::string> vals;
				while (std::getline(sstream, item, ',')) {
					if(type==0){
						type = item.at(0);
					}else{
						vals.push_back(item);
					}//endif
				}//else while
				
				if(type =='e' || type == 'E'){
					I source =	(I) std::stoll(vals.at(0),0,10);
					I target =  (I) std::stoll(vals.at(1),0,10);
					T cost  = (T) std::stold(vals.at(2),0);
					Edge<T,I> edge ( source, target, cost );
					this->edges.push_back(edge);
				}
				else if(type ==  'N' || type =='n'){
						I id = (I) std::stoll(vals.at(0),0,10);
						Node<I> node (id, vals.at(1) );
						add_node(node);
				}
				else if(type ==  'T' || type =='t'){
						I id = (I) std::stoll(vals.at(0),0,10);
						//Node<I> node (id, vals.at(1) );
						targets.push_back(id);
				}
				else if(type ==  'S' || type =='s'){
						I id = (I) std::stoll(vals.at(0),0,10);
						source= new Node<I> (id, vals.at(1) );

				}

			}
		public:
			Graph(){
				source = nullptr;
				next_id = 0;
			}
			~Graph(){
				if(source != nullptr){
					delete source;
					source = nullptr;
				}
			}

			// &result result vector of neighbor ids
			void successor(I &node, std::vector<Edge<T,I>> &result){
				for(auto e : edges){
					if(e.get_source() == node ){
						result.push_back(e);
					}
				}
			}
			void get_edges(std::vector<betacore::Edge<T,I>> &edges){
					edges.push_back(this->edges);
			}
			Node<I> get_node(I id){
				auto pred = [id](const Node<I> &item) {
					return item.get_id() == id;
				};
				auto n = std::find(this->nodes.begin(), this->nodes.end(), pred);
				return ( n != this->nodes.end())?n:NULL;
			}
			void add_node(){

				this->nodes.push_back(node);
			}
			void remove_node(I id){
				auto pred = [id](const Node<I> &item) {
					return item.get_id() == id;
				};
				this->nodes.erase(std::remove_if(this->nodes.begin(), this->nodes.end(), pred));
			}
			void load_from_file(std::string file_path){
				std::ifstream file;
				file.exceptions( std::ifstream::badbit);
				try {
					file.open (file_path);
					std::string line;
					while (std::getline(file, line))
					{
						parse_line(line);
						std::cout << line <<std::endl;
					}
				}catch (const std::ifstream::failure& e) {
					std::cout << "Exception opening/reading file"<< e.what() <<std::endl;
				}
				file.close();
			}
			I get_source(){
				return this->source->get_id();
			}
			I get_next_id(){
				return next_id++;
			}
			void get_targets(std::vector<I> &targets){
				targets.insert(std::end(targets), std::begin(this->targets), std::end(this->targets));
			}

			//Running time O(N)
			T cost(I u, I ui){
				for(auto e : this->edges){
					if( e.get_source() == u && e.get_target() == ui){
						
						return e.get_cost();
					}
				}
				return (T) 0.0;
			}
			void print(){
				for(auto e : this->edges){
					std::cout<< "Edge:" << e.get_source() << "->" << e.get_target() << " cost:"<< e.get_cost() << std::endl;
				}
				for(auto n : this->nodes){
					std::cout<<"Nodes:" <<n.get_id() << std::endl;
				}
			}
	};
}
#endif