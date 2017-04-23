#ifndef ASTAR_H
#define ASTAR_H

#include "Path.hpp"
#include "Node.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

namespace nm{
	
class Astar{

	public:
		Astar();
		static std::vector<unsigned int> run(std::vector<Node> &, unsigned int, unsigned int, sf::RenderWindow &);
		
};

}

#endif