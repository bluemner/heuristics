#include <iostream>
#include <functional>
#include "../headers/dijkstra.hpp"
#include "../headers/node.hpp"
#include "../headers/edge.hpp"
#include "../headers/graph.hpp"

// The evil's of c++ templates
typedef double T;
typedef long long I;

betacore::Graph<T, I> G;
betacore::Dijkstra<T,I> dijkstra;

//This fuction can be changed if you want :-) to do some successor thing...
void successor(I &node, std::vector<betacore::Edge<T,I>> &result){
	G.successor(node,result);
}
//Node this has to be type T
T cost(I u, I ui){
	return G.cost(u,ui);
}

int main (int argc, char * argv[]){
	std::cout<<"_______________________________________________________________"<<std::endl;
	std::cout<<"Heuristics"<<std::endl;
	std::cout<<"_______________________________________________________________"<<std::endl;
	if(argc < 3){
		std::cout<< "Usage:\n" << "\tPlease Provide path to graph .csv\n\tPlease provide a source id" <<std::endl;
	}
	else
	{
		std::string file_path(argv[1]);
		I source = (I) std::stoll(argv[2],0,10);
		std::cout << file_path << std::endl;
		
		G.load_from_file(file_path);	
		std::cout<<"_______________________________________________________________"<<std::endl;
		G.print();
		std::cout<<"_______________________________________________________________"<<std::endl;
		std::map<I,I> path;

		std::function<T( I u , I ui)> cost_function = cost;
		std::function<void(I &, std::vector<betacore::Edge<T,I>> &)> successor_function = successor;
	
		// try{
		// 	dijkstra.run(source,1,path,cost_function,successor_function);
		// }catch(const std::exception& e){

		// }
		// path.clear();
		// try{
		// 	dijkstra.run(source,9,path,cost_function,successor_function);
		// }catch(const std::exception& e){
			
		// }
		// 	path.clear();
		try{
			std::vector<I> targets={1,9};
			dijkstra.run(source,targets,path, cost_function, successor_function);
		}catch(const std::exception& e){
			
		}
	}
	std::cout<<"_______________________________________________________________"<<std::endl;
	return 0;
}

