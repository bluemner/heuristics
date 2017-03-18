#ifndef _betacore_node_hpp_
#define _betacore_node_hpp_

namespace betacore{
	template<typename I>
	class Node{
		private:
		I id;
		std::string name;
		public:
			Node(I &id,std::string &name){
				this->id = id;
				this->name = name;
			}
			std::string get_name(){
				return this->name;
			}
			void setName(const std::string &name){
				this->name = std::string(name);
			}
			I get_id(){
				return this.id;
			}
	};
}
#endif