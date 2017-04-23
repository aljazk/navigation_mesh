#include "Text.hpp"

Text::Text(){
	setColor(sf::Color(0,0,0,0));
	setName("Text");
	alignText();
}

bool Text::click(const sf::Vector2i mouse){
	if (mouse.x < 1){
		//to avoid warning
	}
	return 0;
}