#include "Input.hpp"

Input::Input(){
	setName("My name");
	setTextColor(sf::Color::Black);
	setSize(sf::Vector2f(200,30));
	setColor(sf::Color::White);
	setBorderWidth(1);
	
	border_color = sf::Color(200,200,200,255);
	hover_border_color = sf::Color(130,130,130,255);
	click_border_color = sf::Color(170,255,255);
	
	alignText();
}

void Input::hover(const sf::Vector2i mouse){
	if(mode != 2){
		if(mouse.x > position.x && mouse.x < position.x+size.x && mouse.y > position.y && mouse.y < position.y+size.y){
			mode = 1;
		} else {
			mode = 0;
		}
	}
}

bool Input::click(const sf::Vector2i mouse){
	if(mouse.x > position.x && mouse.x < position.x+size.x && mouse.y > position.y && mouse.y < position.y+size.y){
		mode = 2;
		return 1;
	} else mode = 0;
	return 0;
}