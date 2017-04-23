#include "Path.hpp"

using namespace nm;

Path::Path(){
	cost = 0;
	weight = 0;
	dead = false;
}

void Path::move(const unsigned int id, const unsigned int cost, Node &current_node, Node &end_node){
	ids.push_back(id);
	this->cost += cost;
	weight = this->cost + current_node.getH(end_node)*1.5;
	//weight = current_node.getH(end_node);
}