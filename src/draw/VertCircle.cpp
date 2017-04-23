
#include "VertCircle.hpp"

VertCircle::VertCircle(){
	pos.x = 0;
	pos.y = 0;
	radius = 0;
	edges = radius/2;
	if(edges < 30){
		edges = 30;
	}
	color = sf::Color::Blue;
}

VertCircle::VertCircle(const sf::Vector2f newPos, const float newRad){
	pos = newPos;
	radius = newRad;
	edges = radius/2;
	if(edges < 30){
		edges = 30;
	}
	color = sf::Color::Blue;
}

void VertCircle::set(const sf::Vector2f newPos, const float newRad){
	pos = newPos;
	radius = newRad;
}

void VertCircle::add(sf::VertexArray &vert){
	sf::Vertex vertex;
	vertex.position = pos;
	vertex.color = sf::Color::Transparent;
	vert.append(vertex);
	vertex.position = pos;
	vertex.color = color;
	vert.append(vertex);
	float def = 6.28 / edges;
	for(float a=0; a<6.29+def; a+= def){
		sf::Vector2f center = pos;
		center.x += radius * cos(a);
		center.y += radius * sin(a);
		vertex.position = center;
		vert.append(vertex);
		vertex.position = pos;
		vert.append(vertex);
	}
	vertex.position = pos;
	vertex.color = sf::Color::Transparent;
	vert.append(vertex);
	
}

void VertCircle::addLine(sf::VertexArray &vert){
	sf::Vertex vertex;
	float def = 6.28 / edges;
	
	vertex.color = sf::Color::Transparent;
	sf::Vector2f center = pos;
	center.x += radius * cos(0);
	center.y += radius * sin(0);
	vertex.position = center;
	vert.append(vertex);
	
	vertex.color = color;
	for(float a=0; a<6.29+def; a+= def){
		sf::Vector2f center = pos;
		center.x += radius * cos(a);
		center.y += radius * sin(a);
		vertex.position = center;
		vert.append(vertex);
	}
	
	vertex.color = sf::Color::Transparent;
	vert.append(vertex);
	
}

void VertCircle::setColor(const sf::Color newColor){
	color = newColor;
}