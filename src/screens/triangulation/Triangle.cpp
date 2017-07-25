#include "Triangle.hpp"

Triangle::Triangle(){
	
}

Triangle::Triangle(std::vector<Vertex> p){
	if(!checkCW(p)){
		Vertex v = p[0];
		p[0] = p[1];
		p[1] = v;
	}
	for(unsigned int i=0; i<p.size()-1; i++){
		edges.push_back(std::make_shared<Edge>(Edge(p[i], p[i+1])));
	}
	edges.push_back(std::make_shared<Edge>(Edge(p[p.size()-1], p[0])));
}

bool Triangle::checkCW(const std::vector<Vertex> &p){
	int res = 0;
	for(unsigned int i=0; i<p.size()-1; i++){
		res += (p[i+1].x-p[i].x)*(p[i+1].y+p[i].y);
	}
	res += (p[0].x-p[p.size()-1].x)*(p[0].y+p[p.size()-1].y);
	return (res > 0);
}

std::vector<std::shared_ptr<Edge>> Triangle::getOpenEdges(){
	std::vector<std::shared_ptr<Edge>> oe;
	for(unsigned int i=0; i<edges.size(); i++){
		if(edges[i]->isOpen()){
			oe.push_back(edges[i]);
		}
	}
	return oe;
}

unsigned int Triangle::openEdgeCount(){
	unsigned int c = 0;
	for(unsigned int i=0; i<edges.size(); i++){
		if(edges[i]->isOpen()){
			c++;
		}
	}
	return c;
}

bool Triangle::edgeIsOpen(){
	return openEdgeCount() > 0;
}

void Triangle::getVert(sf::VertexArray &vert){
	for(unsigned int i=0; i<edges.size(); i++){
		sf::Vertex v;
		if(edges[i]->isOpen()){
			v.color = sf::Color::White;
		} else {
			v.color = sf::Color::Red;
		}
		v.position.x = edges[i]->getPoint1().x;
		v.position.y = edges[i]->getPoint1().y;
		vert.append(v);
		v.position.x = edges[i]->getPoint2().x;
		v.position.y = edges[i]->getPoint2().y;
		vert.append(v);
	}
}