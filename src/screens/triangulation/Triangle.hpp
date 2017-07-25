#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Edge.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class Triangle{
		std::vector<std::shared_ptr<Edge>> edges;
		bool checkCW(const std::vector<Vertex> &);
	public:
		Triangle();
		Triangle(std::vector<Vertex>); //points are always added in clockwise order
		std::vector<std::shared_ptr<Edge>> getOpenEdges();
		unsigned int openEdgeCount();
		bool edgeIsOpen();
		void getVert(sf::VertexArray &);
};

#endif