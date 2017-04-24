#include <iostream>
#include <functional>
#include <chrono>
#include <ctime>
#include <random>
#include "../headers/dijkstra.hpp"
#include "../headers/node.hpp"
#include "../headers/edge.hpp"
#include "../headers/graph.hpp"

// The evil's of c++ templates
typedef long long T;
typedef long long I;


betacore::Graph<T, I> G;
betacore::Dijkstra<T,I> dijkstra;
unsigned int size;

T cost_check_g(I u, I ui) {
	//Null guard & data check
	std::string n0(G.get_node_name(u));
	std::string n1(G.get_node_name(ui));

	I different_cost = 0;
	bool different = false;
	for (unsigned int i = 0; i < n1.length(); i++) {
		//std::cout << "N0:" << n0[i] << "\tN1:" << n1[i] <<std::endl;
		if (different) {
			if (n0.at(i) != n1.at(i)) {
				different = false;
			} else {
				++different_cost;
			}
		}
		if (n0.at(i) != n1.at(i)) {
			different = true;
		}
	}
	return different_cost; // -1 for fence post
}

T cost_check_h(I ui) {
	char a = 'A';
	char b = 'B';
	char e = 'E';
	T cost = 0;
	//count A's to the right of B
	std::string n(G.get_node_name(ui));
	bool b_found= false;	
	for (unsigned int  i = 0; i < size; i++) {
		if(n[i]!= a){
			cost+=1;
		}
		if(n[i+size] !=b){
			cost+=1;
		}
	}

	if (n[n.length() - 1] != e) {
		++cost;
	}
	return (T) cost;
}
//Node this has to be type T
T cost(I u, I ui){
	if(u<0 && ui < 0){
		//To Do exception
	}else if(u==ui){
		return cost_check_h(ui); //return the cost for the heuristic function
	}
	return cost_check_g(u,ui) + cost_check_h(ui);
}

//Dijkstra cost function
T cost_dijkstra(I u, I ui){
	if(u<0 && ui < 0){
		//To Do exception
	}else if(u <0){
		return 0; //return the cost for the heuristic function
	}
	return cost_check_g(u,ui);
}
//This fuction can be changed if you want :-) to do some successor thing...
void successor(I &node, std::vector<betacore::Edge<T,I>> &result){
	std::string n = G.get_node_name(node);

	for(unsigned int  i=0; i< n.length(); i++){		
		for(unsigned int j=0; j<n.length(); j++){
			std::string temp(n);
			temp.at(i) = n.at(j);
			temp.at(j) = n.at(i);
		
			I contains = G.contains(temp);
			I target_id;
			if( contains!=0){
				target_id = contains;	
				
			}else{
				target_id = G.get_next_id();
				betacore::Node<I> target_node(target_id,temp);
				G.add_node(target_node);
			}
			if( node ==target_id){
				//std::cout<<"same:" << n << "::" << temp <<std::endl;
			}else{		
				//Get cost to node
				T cst = cost(node,target_id);
				//Add Edge
				betacore::Edge<T,I> edge(node,target_id,cst);
				G.add_edge(edge);
				result.push_back(edge);	
			}
		}
	}



}

std::string make_source_string(){
	//Create string of size
	std::string temp(size * 2 +1, 'E');
	for(unsigned int i=1;  i < size + 1; ++i){
		temp.at(i)='B';
		temp.at(i+size)='A';
	}
	//				  EBBBBBAAAAAAB
	//std::string temp("AAAAAEBBBBBAB");
	return temp;
}
std::string make_goal_string(){
	//Create string of size
	std::string temp(size * 2 +1, 'E');
	for(unsigned int i=0; i <size; ++i){
		temp.at(i)='A';
		temp.at(i+size)='B';
	}

	return temp;
}

std::string make_random_string(){
	std::random_device rd;
	std::mt19937_64 e2(rd());
	std::uniform_real_distribution<> dist(0, 2);
	//Create a string of all e's
	std::string temp(size * 2 +1,'E');
	std::map<char,unsigned int> vals= {{'A',0},{'B',0},{'E',0}};
	std::vector<char> val = {'A','B','E'};
	bool removed_a=false;
	bool removed_b=false;
	
	unsigned int skip = (unsigned int) dist(e2) + 2  % ( size *2 );
	for(unsigned int i=0; i <size * 2 +1; ++i ){
		
		 if(skip ==i){
			vals.erase('E');
			val.erase(std::remove(val.begin(), val.end(), 'E'), val.end());
			continue;
		}
		 char letter  =  (val.size()==1)? val[0]  : val.at(( (int) dist(e2)  ) % ( val.size()-1));
		 temp.at(i) = letter;
		 vals[letter]+=1; 

		if(!removed_a && vals['A']== size){
			vals.erase('A');
			val.erase(std::remove(val.begin(), val.end(), 'A'), val.end());
			removed_a=true;
		}
		if(!removed_b && vals['B']== size ){
			vals.erase('B');
			val.erase(std::remove(val.begin(), val.end(), 'B'), val.end());
			removed_b=true;
		}
	
	}
	return temp;
}

void run_random_h(std::string source,std::string target){
			std::cout<<"_______________________________________________________________"<<std::endl;
			std::cout<<"Random Start with Heuristics"<<std::endl;
			std::cout<<"_______________________________________________________________"<<std::endl;	
			I source_id = G.get_next_id();
			betacore::Node<I> source_node(source_id,source);
			I target_id = G.get_next_id();
			betacore::Node<I> target_node(target_id,target);
			G.add_node(source_node);
			G.add_node(target_node);
			std::cout<<"Inital state of graph (remaining graph will be created during run)"<<std::endl;
			G.print();
			try{
				std::map<I,I> path;
				std::function<T( I u , I ui)> cost_function = cost;
				std::function<void(I &, std::vector<betacore::Edge<T,I>> &)> successor_function = successor;
		
				std::vector<I> targets;
				targets.push_back(target_id);
				auto start = std::chrono::system_clock::now();
				auto start_cpu = std::clock();
				dijkstra.run(source_id,targets,path, cost_function, successor_function);
				auto end = std::chrono::system_clock::now();
				auto end_cpu = std::clock();
				std::chrono::duration<double> diff = end-start;
				std::cout<< "Running time(includes std::cout):\t" << diff.count() <<"s" << std::endl;			
				std::cout<< "cpu start: "<< start_cpu << "\t" <<"cpu end:"<<end_cpu<<"\tCLOCKS_PER_SEC:"<<CLOCKS_PER_SEC  <<std::endl;		
				double cpu = (end_cpu - start_cpu) / (double)CLOCKS_PER_SEC ;
				
				std::cout<< "cpu time(includes std::cout):\t" <<cpu<<"s" << std::endl;


				I mp = path[target_id];
				std::cout<<"path:\n";				
				std::cout<< G.get_node_name(target_id) <<"<-";
				while (mp !=source_id){
					if(!path.count(mp)){
						std::cerr<<"Path from sink doesn't lead back to source" <<"\n";
					
					}
					std::cout<< G.get_node_name(mp) <<"<-";
					mp = path[mp];
				}
				std::cout<< source << "\n";
			
				//G.print();
			}catch(const std::exception& e){
				std::cout<<"Problem with algorithm" <<std::endl;
			}

}
void run_random_0(std::string source,std::string target){
			std::cout<<"_______________________________________________________________"<<std::endl;
			std::cout<<"Random Start with out Heuristics"<<std::endl;
			std::cout<<"_______________________________________________________________"<<std::endl;	
			I source_id = G.get_next_id();
			betacore::Node<I> source_node(source_id,source);
			I target_id = G.get_next_id();
			betacore::Node<I> target_node(target_id,target);
			G.add_node(source_node);
			G.add_node(target_node);
			std::cout<<"Inital state of graph (remaining graph will be created during run)"<<std::endl;
			G.print();
			try{
				std::map<I,I> path;
				std::function<T( I u , I ui)> cost_function = cost_dijkstra;
				std::function<void(I &, std::vector<betacore::Edge<T,I>> &)> successor_function = successor;
		
				std::vector<I> targets;
				targets.push_back(target_id);
				auto start = std::chrono::system_clock::now();
				auto start_cpu = std::clock();
				dijkstra.run(source_id,targets,path, cost_function, successor_function);
				auto end = std::chrono::system_clock::now();
				auto end_cpu = std::clock();
				std::chrono::duration<double> diff = end-start;
				std::cout<< "Running time(includes std::cout):\t" << diff.count() <<"s" << std::endl;			
				std::cout<< "cpu start: "<< start_cpu << "\t" <<"cpu end:"<<end_cpu<<"\tCLOCKS_PER_SEC:"<<CLOCKS_PER_SEC  <<std::endl;		
				double cpu = (end_cpu - start_cpu) / (double)CLOCKS_PER_SEC ;
				
				std::cout<< "cpu time(includes std::cout):\t" <<cpu<<"s" << std::endl;


				I mp = path[target_id];
				std::cout<<"path:\n";				
				std::cout<< G.get_node_name(target_id) <<"<-";
				while (mp !=source_id){
					if(!path.count(mp)){
						std::cerr<<"Path from sink doesn't lead back to source" <<"\n";
					
					}
					std::cout<< G.get_node_name(mp) <<"<-";
					mp = path[mp];
				}
				std::cout<< source << "\n";
			
				//G.print();
			}catch(const std::exception& e){
				std::cout<<"Problem with algorithm" <<std::endl;
			}
}
void required_run_h(std::string source,std::string target){
		std::cout<<"_______________________________________________________________"<<std::endl;
		std::cout<<" Required Start with Heuristics"<<std::endl;
		std::cout<<"_______________________________________________________________"<<std::endl;	
		I source_id = G.get_next_id();
		betacore::Node<I> source_node(source_id,source);
		I target_id = G.get_next_id();
		betacore::Node<I> target_node(target_id,target);
		G.add_node(source_node);
		G.add_node(target_node);



	
		std::cout<<"Inital state of graph (remaining graph will be created during run)"<<std::endl;
		G.print();

		// std::vector<betacore::Edge<T,I>> result;
		// successor(source_id, result);
		// G.print();

		std::cout<<"Running A*" <<std::endl;
		try{
			std::map<I,I> path;
	 		std::function<T( I u , I ui)> cost_function = cost;
	 		std::function<void(I &, std::vector<betacore::Edge<T,I>> &)> successor_function = successor;
	
			std::vector<I> targets;
			targets.push_back(target_id);
			auto start = std::chrono::system_clock::now();
			auto start_cpu = std::clock();
			dijkstra.run(source_id,targets,path, cost_function, successor_function);
			auto end = std::chrono::system_clock::now();
			auto end_cpu = std::clock();
			std::chrono::duration<double> diff = end-start;
			std::cout<< "Running time(includes std::cout):\t" << diff.count() <<"s" << std::endl;			
			std::cout<< "cpu start: "<< start_cpu << "\t" <<"cpu end:"<<end_cpu<<"\tCLOCKS_PER_SEC:"<<CLOCKS_PER_SEC  <<std::endl;		
			double cpu = (end_cpu - start_cpu) / (double)CLOCKS_PER_SEC ;
			
			std::cout<< "cpu time(includes std::cout):\t" <<cpu<<"s" << std::endl;


			I mp = path[target_id];
			std::cout<<"path:\n";				
			std::cout<< G.get_node_name(target_id) <<"<-";
			while (mp !=source_id){
				if(!path.count(mp)){
					std::cerr<<"Path from sink doesn't lead back to source" <<"\n";
				
				}
				std::cout<< G.get_node_name(mp) <<"<-";
				mp = path[mp];
			}
			std::cout<< source << "\n";
		
			//G.print();
		}catch(const std::exception& e){
			std::cout<<"Problem with algorithm" <<std::endl;
	 	}
}
void required_run_0(std::string source,std::string target){
		std::cout<<"_______________________________________________________________"<<std::endl;
		std::cout<<"Required Start with out Heuristics"<<std::endl;
		std::cout<<"_______________________________________________________________"<<std::endl;	
		I source_id = G.get_next_id();
		betacore::Node<I> source_node(source_id,source);
		I target_id = G.get_next_id();
		betacore::Node<I> target_node(target_id,target);
		G.add_node(source_node);
		G.add_node(target_node);



	
		std::cout<<"Inital state of graph (remaining graph will be created during run)"<<std::endl;
		G.print();

		// std::vector<betacore::Edge<T,I>> result;
		// successor(source_id, result);
		// G.print();

		std::cout<<"Running A*" <<std::endl;
		try{
			std::map<I,I> path;
	 		std::function<T( I u , I ui)> cost_function = cost_dijkstra;
	 		std::function<void(I &, std::vector<betacore::Edge<T,I>> &)> successor_function = successor;
	
			std::vector<I> targets;
			targets.push_back(target_id);
			auto start = std::chrono::system_clock::now();
			auto start_cpu = std::clock();
			dijkstra.run(source_id,targets,path, cost_function, successor_function);
			auto end = std::chrono::system_clock::now();
			auto end_cpu = std::clock();
			std::chrono::duration<double> diff = end-start;
			std::cout<< "Running time(includes std::cout):\t" << diff.count() <<"s" << std::endl;			
			std::cout<< "cpu start: "<< start_cpu << "\t" <<"cpu end:"<<end_cpu<<"\tCLOCKS_PER_SEC:"<<CLOCKS_PER_SEC  <<std::endl;		
			double cpu = (end_cpu - start_cpu) / (double)CLOCKS_PER_SEC ;
			
			std::cout<< "cpu time(includes std::cout):\t" <<cpu<<"s" << std::endl;


			I mp = path[target_id];
			std::cout<<"path:\n";				
			std::cout<< G.get_node_name(target_id) <<"<-";
			while (mp !=source_id){
				if(!path.count(mp)){
					std::cerr<<"Path from sink doesn't lead back to source" <<"\n";
				
				}
				std::cout<< G.get_node_name(mp) <<"<-";
				mp = path[mp];
			}
			std::cout<< source << "\n";
		
			//G.print();
		}catch(const std::exception& e){
			std::cout<<"Problem with algorithm" <<std::endl;
	 	}
}
/**
 *
 */
int main (int argc, char * argv[]){
	std::cout<<"_______________________________________________________________"<<std::endl;
	std::cout<<"Heuristics"<<std::endl;
	std::cout<<"_______________________________________________________________"<<std::endl;
	if(argc < 2){
			std::cout<< "Usage:\n" << "\tPlease Provide the size of the puzzle" <<std::endl;
	}
	else
	{
		size= (unsigned int) std::stoi(argv[1]);
		
		
		std::string source = make_source_string();
		std::string target = make_goal_string();
	
		//Run A:
		for(int i=0; i< 10;++i){	
			std::string a = make_random_string();
			run_random_h(a,target);
			G.clear();
			run_random_0(a,target);
			G.clear();
		}
		required_run_h(source,target);
		G.clear();
		required_run_0(source,target);
	}
	
	std::cout<<"_______________________________________________________________"<<std::endl;
	return 0;
}

