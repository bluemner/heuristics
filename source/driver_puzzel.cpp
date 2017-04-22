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
std::string make_source_string(int size){
	//Create string of size
	std::string temp(size * 2 +1, 'E');
	for(int i=1; i <size + 1; ++i){
		temp.at(i)='B';
		temp.at(i+size)='A';
	}
	return temp;
}
std::string make_goal_string(int size){
	//Create string of size
	std::string temp(size * 2 +1, 'E');
	for(int i=0; i <size; ++i){
		temp.at(i)='A';
		temp.at(i+size)='B';
	}

	
	return temp;
}

int main (int argc, char * argv[]){
	std::cout<<"_______________________________________________________________"<<std::endl;
	std::cout<<"Heuristics"<<std::endl;
	std::cout<<"_______________________________________________________________"<<std::endl;
	if(argc < 2){
			std::cout<< "Usage:\n" << "\tPlease Provide the size of the puzzle" <<std::endl;
	}
	else
	{
		
		// std::string file_path(argv[1]);
		
		// std::cout << file_path << std::endl;
		
		// G.load_from_file(file_path);	
		int word_size = (int) std::stoi(argv[1]);
		
		std::string source = make_source_string(word_size);
		std::string target = make_goal_string(word_size);
		betacore::Node source_node(G.get_next_id(),source);
		betacore::Node target_node(G.get_next_id(),target);
		G.add_node();


		std::cout<< "Source:\t" << source <<std::endl;
		std::cout<< "Target:\t" << target <<std::endl;

		// std::cout<<"_______________________________________________________________"<<std::endl;
		// G.print();
		// std::cout<<"_______________________________________________________________"<<std::endl;
		// std::map<I,I> path;
		// G.add_node();

		// G.add_node();
		// std::function<T( I u , I ui)> cost_function = cost;
		// std::function<void(I &, std::vector<betacore::Edge<T,I>> &)> successor_function = successor;

		
		// try{
		// 	std::vector<I> targets;
		// 	G.get_targets(targets);
		// 	auto start = std::chrono::system_clock::now();
		// 	auto start_cpu = std::clock();
		// 	dijkstra.run(source,targets,path, cost_function, successor_function);
		// 	auto end = std::chrono::system_clock::now();
		// 	auto end_cpu = std::clock();
		// 	std::chrono::duration<double> diff = end-start;
		// 	std::cout<< "Running time(includes std::cout):\t" << diff.count() <<"s" << std::endl;			
		// 	std::cout<< "cpu start: "<< start_cpu << "\t" <<"cpu end:"<<end_cpu<<"\tCLOCKS_PER_SEC:"<<CLOCKS_PER_SEC  <<std::endl;		
		// 	double cpu = (end_cpu - start_cpu) / (double)CLOCKS_PER_SEC ;
			
		// 	std::cout<< "cpu time(includes std::cout):\t" <<cpu<<"s" << std::endl;
		// }catch(const std::exception& e){
			
		//}
	}
	
	std::cout<<"_______________________________________________________________"<<std::endl;
	return 0;
}

