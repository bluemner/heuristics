#ifndef _betacore_graph_hpp_
#define _betacore_graph_hpp_
#include "./node.hpp"
#include "./edge.hpp"
#include <vector>

namespace betacore{
	template<typename T, typename I>
	class Graph{
		private:
			std::vector<betacore::Node<I>> nodes;
			std::vector<betacore::Edge<T,I>> edges;
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

			}
		public:
			Graph(){}

			// &result result vector of neighbor ids
			void successor(I &node, std::vector<Edge<T,I>> &result){
				for(auto e : edges){
					if(e.get_source() == node ){
						result.push_back(e);
					}
				}
			}
			Node<I> get_node(I id){
				auto pred = [id](const Node<I> &item) {
					return item.get_id() == id;
				};
				auto n = std::find(this->nodes.begin(), this->nodes.end(), pred);
				return ( n != this->nodes.end())?n:NULL;
			}
			void add_node(Node<I> &node){
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
	};
}
#endif