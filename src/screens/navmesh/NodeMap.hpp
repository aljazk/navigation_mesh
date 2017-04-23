#ifndef NODEMAP_H
#define NODEMAP_H

#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include <iostream>
#include "Astar.hpp"
#include <cstdlib>

namespace nm{
	
class NodeMap{
		std::vector<Node> nodes;
		void findNeighbors();
	public:
		NodeMap();
		void draw(sf::RenderWindow &);
};

}

#endif