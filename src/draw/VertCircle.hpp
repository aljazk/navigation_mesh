#ifndef VERTCIRCLE_H
#define VERTCIRCLE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class VertCircle{
		sf::Vector2f pos;
		float radius;
		sf::Color color;
	public:
		int edges;
		VertCircle();
		VertCircle(const sf::Vector2f, const float);
		void set(const sf::Vector2f, const float);
		void add(sf::VertexArray&);
		void addLine(sf::VertexArray&);
		void setColor(const sf::Color);
		
}; 

#endif