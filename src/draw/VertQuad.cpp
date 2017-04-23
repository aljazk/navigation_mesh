#include "VertQuad.hpp"

VertQuad::VertQuad(){
	texPos.x = 0;
	texPos.y = 0;
	texSize.x = 0;
	texSize.y = 0;
	objPos.x = 0;
	objPos.y = 0;
	objSize.x = 0;
	objSize.y = 0;
	center.x = 0;
	center.y = 0;
	angle = atan(1)*2;
}

VertQuad::VertQuad(const sf::Vector2f newTexPos, const sf::Vector2f newTexSize, const sf::Vector2f newObjPos){
	set(newTexPos, newTexSize, newObjPos);
}

VertQuad::VertQuad(const sf::Vector2f newTexPos, const sf::Vector2f newTexSize, const sf::Vector2f newObjPos, const sf::Vector2f newObjSize){
	set(newTexPos, newTexSize, newObjPos, newObjSize);
}

void VertQuad::set(const sf::Vector2f newTexPos, const sf::Vector2f newTexSize, const sf::Vector2f newObjPos){
	texPos = newTexPos;
	texSize = newTexSize;
	objPos = newObjPos;
	objSize = newTexSize;
	setCenter();
	angle = atan(1)*2;
	color = sf::Color::White;
}

void VertQuad::set(const sf::Vector2f newTexPos, const sf::Vector2f newTexSize, const sf::Vector2f newObjPos, const sf::Vector2f newObjSize){
	texPos = newTexPos;
	texSize = newTexSize;
	objPos = newObjPos;
	objSize = newObjSize;
	setCenter();
	angle = atan(1)*2;
	color = sf::Color::White;
}

void VertQuad::setCenter(){
	center.x = objSize.x/2;
	center.y = objSize.y/2;
}

void VertQuad::setCenter(const sf::Vector2f newCenter){
	center = newCenter;
}

void VertQuad::setAngle(const float newAngle){
	angle = newAngle;
}
	
void VertQuad::rotateVertex(float &cx, float &cy){
	float f = atan2(cx,cy)+(float)angle;
	float dist = sqrt(pow(cx, 2)+pow(cy, 2));
	cx = cos(f)*dist;
	cy = sin(f)*dist;
}

void VertQuad::setColor(const sf::Color newColor){
	color = newColor;
}
	
void VertQuad::add(sf::VertexArray &vert){
	sf::Vertex vertex;
	float cx, cy;
	cx = -center.x;
	cy = -center.y;
	rotateVertex(cx, cy);
	vertex.position = sf::Vector2f(objPos.x+cx, objPos.y+cy);
	vertex.texCoords = sf::Vector2f(texPos.x+texSize.x, texPos.y);
	vertex.color = color;
	vert.append(vertex);
	cx = -center.x+objSize.x;
	cy = -center.y; 
	rotateVertex(cx, cy);
	vertex.position = sf::Vector2f(objPos.x+cx, objPos.y+cy);
	vertex.texCoords = sf::Vector2f(texPos.x, texPos.y);
	vertex.color = color;
	vert.append(vertex);
	cx = -center.x+objSize.x;
	cy = -center.y+objSize.y;
	rotateVertex(cx, cy);
	vertex.position = sf::Vector2f(objPos.x+cx, objPos.y+cy);
	vertex.texCoords = sf::Vector2f(texPos.x, texPos.y+texSize.y);
	vertex.color = color;
	vert.append(vertex);
	cx = -center.x;
	cy = -center.y+objSize.y; 
	rotateVertex(cx, cy);
	vertex.position = sf::Vector2f(objPos.x+cx, objPos.y+cy);
	vertex.texCoords = sf::Vector2f(texPos.x+texSize.x, texPos.y+texSize.y);
	vertex.color = color;
	vert.append(vertex);
	
}