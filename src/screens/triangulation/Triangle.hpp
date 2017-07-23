#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Edge.hpp"

class Triangle{
		std::vector<Edge> edges;
		bool checkCW(const std::vector<Vertex> &);
	public:
		Triangle();
		Triangle(std::vector<Vertex>); //points are always added in clockwise order
		unsigned int openEdgeCount();
		bool edgeIsOpen();
};

#endif