#include "TexturedButton.hpp"

TexturedButton::TexturedButton(){
	setName("TexturedButton");
	setBorderWidth(0);
	setSize(sf::Vector2f(120,30));
	
	texture_position = sf::Vector2f(1,0);
	hover_texture_position = texture_position;
	click_texture_position = texture_position;
	
	texture_size = sf::Vector2f(10,10);
	hover_texture_size = texture_size;
	click_texture_size = texture_size;
	
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