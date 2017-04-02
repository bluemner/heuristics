#include <iostream>
#include <functional>
#include <chrono>
#include <ctime>
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
	if(argc < 2){
		std::cout<< "Usage:\n" << "\tPlease Provide path to graph .csv" <<std::endl;
	}
	else
	{
		std::string file_path(argv[1]);
		
		std::cout << file_path << std::endl;
		
		G.load_from_file(file_path);	
		I source = G.get_source(); //(I) std::stoll(argv[2],0,10);
		
		std::cout<<"_______________________________________________________________"<<std::endl;
		G.print();
		std::cout<<"_______________________________________________________________"<<std::endl;
		std::map<I,I> path;

		std::function<T( I u , I ui)> cost_function = cost;
		std::function<void(I &, std::vector<betacore::Edge<T,I>> &)> successor_function = successor;
	
		try{
			std::vector<I> targets;
			G.get_targets(targets);
			auto start = std::chrono::system_clock::now();
			auto start_cpu = std::clock();
			dijkstra.run(source,targets,path, cost_function, successor_function);
			auto end = std::chrono::system_clock::now();
			auto end_cpu = std::clock();
			std::chrono::duration<double> diff = end-start;
			std::cout<< "Running time(includes std::cout):\t" << diff.count() <<"s" << std::endl;			
			std::cout<< "cpu start: "<< start_cpu << "\t" <<"cpu end:"<<end_cpu<<"\tCLOCKS_PER_SEC:"<<CLOCKS_PER_SEC  <<std::endl;		
			double cpu = (end_cpu - start_cpu) / (double)CLOCKS_PER_SEC ;
			
			std::cout<< "cpu time(includes std::cout):\t" <<cpu<<"s" << std::endl;
		}catch(const std::exception& e){
			
		}
	}
	std::cout<<"_______________________________________________________________"<<std::endl;
	return 0;
}

