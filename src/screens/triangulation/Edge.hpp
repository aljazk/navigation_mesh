#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include "Vertex.hpp"

class Edge{
		//if you're looking from point1 towords point2, the outside of edge is on the left side (clockwise)
		Vertex point1;
		Vertex point2;
		bool open;
	public:
		Edge();
		Edge(Vertex, Vertex);
		bool isOpen();
		void close();
		bool checkSide(Vertex);
		bool checkSide(int, int);
};

#endif