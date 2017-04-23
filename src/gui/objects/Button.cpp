#include "Button.hpp"

Button::Button(){
	setName("Button");
	setBorderWidth(1);
	setSize(sf::Vector2f(120,30));
	
	color = sf::Color(180,180,180,255);
	border_color = sf::Color(200,200,200,255);
	text.setFillColor(sf::Color(50,50,50,255));
	
	hover_color = sf::Color(200,200,200,255);
	hover_border_color = sf::Color(130,130,130,255);
	hover_text.setFillColor(sf::Color(50,50,50,255));
	
	click_color = sf::Color(200,200,200,255);
	click_border_color = sf::Color(170,255,255);
	click_text.setFillColor(sf::Color::Black);
	
	centerText();
}