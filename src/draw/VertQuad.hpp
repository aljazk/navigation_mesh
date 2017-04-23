#ifndef WERTQUAD_H
#define WERTQUAD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class VertQuad{
		sf::Vector2f texPos;
		sf::Vector2f texSize;
		sf::Vector2f objPos;
		sf::Vector2f objSize;
		sf::Vector2f center;
		sf::Color color;
		float angle;
	public:
		VertQuad();
		VertQuad(const sf::Vector2f, const sf::Vector2f, const sf::Vector2f);
		VertQuad(const sf::Vector2f, const sf::Vector2f, const sf::Vector2f, const sf::Vector2f);
		void set(const sf::Vector2f, const sf::Vector2f, const sf::Vector2f);
		void set(const sf::Vector2f, const sf::Vector2f, const sf::Vector2f, const sf::Vector2f);
		void setCenter();
		void setCenter(const sf::Vector2f);
		void setAngle(const float);
		void rotateVertex(float&, float&);
		void setColor(const sf::Color);
		void add(sf::VertexArray&);
		
}; 

#endif // WERTQUAD_H
