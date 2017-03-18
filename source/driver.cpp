#include <iostream>
#include "../headers/dijkstra.hpp"
int main (int argc, char * argv[]){
	std::cout<<"_______________________________________________________________"<<std::endl;
	std::cout<<"Heuristics"<<std::endl;
	std::cout<<"_______________________________________________________________"<<std::endl;
	if(argc < 2){
		std::cout<< "Usage:\n" << "\tPlease Provide path to graph .csv" <<std::endl;
	}else{
	 	std::string file_path(argv[1]);
		std::cout << file_path << std::endl;
		betacore::Graph<double, long long> G;
		G.load_from_file(file_path);
	}
	std::cout<<"_______________________________________________________________"<<std::endl;
	return 0;
}