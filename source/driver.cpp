#include <iostream>
#include <functional>
#include "../headers/dijkstra.hpp"
#include "../headers/node.hpp"
#include "../headers/edge.hpp"
#include "../headers/graph.hpp"

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
	if(argc < 2){
		std::cout<< "Usage:\n" << "\tPlease Provide path to graph .csv" <<std::endl;
	}
	else
	{
		std::string file_path(argv[1]);
		std::cout << file_path << std::endl;
		
		G.load_from_file(file_path);	

		std::map<I,I> path;

		std::function<T( I u , I ui)> cost_function = cost;
		std::function<void(I &, std::vector<betacore::Edge<T,I>> &)> successor_function = successor;
	

		dijkstra.run(1,5,path,cost_function,successor_function);

	}
	std::cout<<"_______________________________________________________________"<<std::endl;
	return 0;
}

