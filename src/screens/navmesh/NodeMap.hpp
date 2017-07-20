#ifndef NODEMAP_H
#define NODEMAP_H

#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include <iostream>
#include "Astar.hpp"
#include <cstdlib>

namespace nm{
	
class NodeMap{
		struct Point{
			int x;
			int y;
			Point(){
				x = 0;
				y = 0;
			}
			Point(int x, int y){
				this->x = x;
				this->y = y;
			}
		};
		std::vector<Node> nodes;
		unsigned int findMin(const Point *, const unsigned int);
		unsigned int dist(const Point, const Point);
		unsigned int findClose(const Point *, const unsigned int, const unsigned int*, const unsigned int);
		unsigned int findClose(const Point *, const std::vector<unsigned int> &, const unsigned int*, const unsigned int);
		void connect(const Point *, const unsigned int);
		void findNeighbors();
		void getLeftRight(std::vector<unsigned int> &, std::vector<Point> &, std::vector<Point> &);
	public:
		NodeMap();
		NodeMap(sf::RenderWindow &);
		void getPath(std::vector<int> &, std::vector<int> &);
		void draw(sf::RenderWindow &);
		void drawNodes(sf::RenderWindow &);
		static void drawPath(const std::vector<int> &, const std::vector<int> &, sf::RenderWindow &);
};


}

#endif