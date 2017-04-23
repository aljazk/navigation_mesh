#include "Alert.hpp"

Alert::Alert(){
	set("Alert");
}

Alert::Alert(const std::string & name){
	set(name);
}

void Alert::set(const std::string & name){
	setName(name);
	
	setTextColor(sf::Color(255,255,255,255));
	setColor(sf::Color(0,0,0,0));
	
	centerText();
	fade = 255;
}

bool Alert::click(const sf::Vector2i mouse){
	if (mouse.x < 1){
		//to avoid warning
	}
	return 0;
}

void Alert::hover(const sf::Vector2i mouse){
	if (mouse.x < 1){
		//to avoid warning
	}
}

void Alert::animate(float ecl){
	position.y -= ecl*10;
	centerText();
	sf::Color text_color = text.getFillColor();
	if (fade > 0)
		fade -= ecl*50;
	text_color.a = (int)fade;
	setTextColor(text_color);
}