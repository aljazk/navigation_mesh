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
		void findNeighbors();
		void getLeftRight(std::vector<unsigned int> &, std::vector<Point> &, std::vector<Point> &);
	public:
		NodeMap();
		void getPath(std::vector<int> &, std::vector<int> &);
		void draw(sf::RenderWindow &);
		static void drawPath(const std::vector<int> path_x, const std::vector<int> path_y, sf::RenderWindow &window){
			sf::VertexArray vpath(sf::LinesStrip);
			for(unsigned int i=0; i<path_x.size(); i++){
				sf::Vertex v(sf::Vector2f(path_x[i], path_y[i]));
				v.color = sf::Color(255,255,0);
				vpath.append(v);
			}
			window.draw(vpath);
		}
};


}

#endif