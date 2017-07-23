#include "Triangle.hpp"

Triangle::Triangle(){
	
}

bool Triangle::checkCW(const std::vector<Vertex> &p){
	int res = 0;
	for(unsigned int i=0; i<p.size()-1; i++){
		res += (p[i+1].x-p[i].x)*(p[i+1].y+p[i].y);
	}
	res += (p[0].x-p[p.size()-1].x)*(p[0].y+p[p.size()-1].y);
	return (res > 0);
}

Triangle::Triangle(std::vector<Vertex> p){
	if(!checkCW(p)){
		Vertex v = p[0];
		p[0] = p[1];
		p[1] = v;
	}
	for(unsigned int i=0; i<p.size()-1; i++){
		edges.push_back(Edge(p[i], p[i+1]));
	}
	edges.push_back(Edge(p[p.size()-1], p[0]));
}

unsigned int Triangle::openEdgeCount(){
	unsigned int c = 0;
	for(unsigned int i=0; i<edges.size(); i++){
		if(edges[i].isOpen()){
			c++;
		}
	}
	return c;
}

bool Triangle::edgeIsOpen(){
	return openEdgeCount() > 0;
}