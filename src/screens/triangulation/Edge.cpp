#include "Edge.hpp"

Edge::Edge(){
	open = true;
}

Edge::Edge(Vertex p1, Vertex p2){
	Edge();
	point1 = p1;
	point2 = p2;
}

bool Edge::isOpen(){
	return open;
}

void Edge::close(){
	open = false;
}

bool Edge::checkSide(Vertex v){
	return checkSide(v.x, v.y);
}

bool Edge::checkSide(int x, int y){
	return ((point2.x - point1.x) * (y - point1.y) - (point2.y - point1.y) * (x - point1.x)) > 0;
}