#include "GUIObject.hpp"

GUIObject::GUIObject(){
	texture_position = sf::Vector2f(0,0);
	hover_texture_position = texture_position;
	click_texture_position = texture_position;
	
	texture_size = sf::Vector2f(0,0);
	hover_texture_size = texture_size;
	click_texture_size = texture_size;
	
	position = sf::Vector2f(100,100);
	hover_position = position;
	click_position = position;
	
	size = sf::Vector2f(200,100);
	hover_size = size;
	click_size = size;
	setBorderWidth(0);
	
	color = sf::Color(100,100,100,255);
	hover_color = color;
	click_color = color;
	
	border_color = sf::Color(0,0,0,255);
	hover_border_color = sf::Color(0,0,0,255);
	click_border_color = sf::Color(0,0,0,255);
	
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setPosition(position);
	text.setString("GUIObject");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	
	hover_text = text;
	click_text = text;
	
	action = "";
	mode = 0;
	centerText();
}

void GUIObject::getVert(sf::VertexArray &vert){
	sf::Vector2f draw_texture_position;
	sf::Vector2f draw_texture_size;
	sf::Vector2f draw_position;
	sf::Vector2f draw_size;
	sf::Color draw_color;
	unsigned int draw_border_width;
	sf::Color draw_border_color;
	if (mode == 0){
		draw_texture_position = texture_position;
		draw_texture_size = texture_size;
		draw_position = position;
		draw_size = size;
		draw_color = color;
		draw_border_width = border_width;
		draw_border_color = border_color;
	} else if (mode == 1){
		draw_texture_position = hover_texture_position;
		draw_texture_size = hover_texture_size;
		draw_position = hover_position;
		draw_size = hover_size;
		draw_color = hover_color;
		draw_border_width = hover_border_width;
		draw_border_color = hover_border_color;
	} else if (mode == 2){
		draw_texture_position = click_texture_position;
		draw_texture_size = click_texture_size;
		draw_position = click_position;
		draw_size = click_size;
		draw_color = click_color;
		draw_border_width = click_border_width;
		draw_border_color = click_border_color;
	}
	VertQuad quad;
	
	//border
	if (draw_border_width > 0){
		sf::Vector2f border_position(draw_position);
		border_position.x -= draw_border_width;
		border_position.y -= draw_border_width;
		sf::Vector2f border_size(draw_size);
		border_size.x += draw_border_width*2;
		border_size.y += draw_border_width*2;
		quad.set(draw_texture_position, draw_texture_size, border_position, border_size);
		quad.setCenter(sf::Vector2f(border_size.x,0));
		quad.setColor(draw_border_color);
		quad.add(vert);
	}
	
	//fill
	quad.set(draw_texture_position, draw_texture_size, draw_position, draw_size);
	quad.setCenter(sf::Vector2f(draw_size.x,0));
	quad.setColor(draw_color);
	quad.add(vert);
	
}

void GUIObject::getText(sf::Text &newText){
	if (mode == 0){
		newText = text;
	} else if (mode == 1){
		newText = hover_text;
	} else if (mode == 2){
		newText = click_text;
	}
}

void GUIObject::animate(float ecl){
	ecl++;
	//nothing
}

void GUIObject::hover(const sf::Vector2i mouse){
	if(mouse.x > position.x && mouse.x < position.x+size.x && mouse.y > position.y && mouse.y < position.y+size.y){
		mode = 1;
	} else {
		mode = 0;
	}
}

bool GUIObject::click(const sf::Vector2i mouse){
	if(mouse.x > position.x && mouse.x < position.x+size.x && mouse.y > position.y && mouse.y < position.y+size.y){
		mode = 2;
		return 1;
	}
	return 0;
}

void GUIObject::addChar(const char newChar){
	std::string name = text.getString();
	if (mode == 2){
		if (newChar == 8){
			if(name.size() > 0){
				name.erase(name.end()-1, name.end());
			}
		} else if (newChar == 127){
			unsigned int er = 0;
			for(unsigned int i=name.size(); i>0; i--){
				if ((name[i-1] > 47 && name[i-1] < 58) ||
					(name[i-1] > 64 && name[i-1] < 91) ||
					(name[i-1] > 96 && name[i-1] < 123)){
						er++;
				} else break;
			}
			name.erase(name.end()-er, name.end());
			if(er == 0){
				name.erase(name.end()-1, name.end());
			}
		} else {
			name.push_back(newChar);
		}
	}
	setName(name);
}

void GUIObject::setTexturePosition(const sf::Vector2f new_texture_position){
	texture_position = new_texture_position;
	hover_texture_position = new_texture_position;
	click_texture_position = new_texture_position;
}

void GUIObject::setTextureSize(const sf::Vector2f new_texture_size){
	texture_size = new_texture_size;
	hover_texture_size = new_texture_size;
	click_texture_size = new_texture_size;
}

void GUIObject::setPosition(const sf::Vector2f new_position){
	position = new_position;
	hover_position = new_position;
	click_position = new_position;
	centerText();
}

void GUIObject::setSize(const sf::Vector2f new_size){
	size = new_size;
	hover_size = new_size;
	click_size = new_size;
}

void GUIObject::setColor(const sf::Color new_color){
	color = new_color;
	hover_color = new_color;
	click_color = new_color;
}

void GUIObject::setBorderWidth(const int newWidth){
	border_width = newWidth;
	hover_border_width = border_width;
	click_border_width = border_width;
}

void GUIObject::setBorderColor(const sf::Color newColor){
	border_color = newColor;
	hover_border_color = border_color;
	click_border_color = border_color;
}

void GUIObject::setText(const sf::Text &new_text){
	text = new_text;
	hover_text = new_text;
	click_text = new_text;
}

void GUIObject::setTextColor(const sf::Color newColor){
	text.setFillColor(newColor);
	hover_text.setFillColor(newColor);
	click_text.setFillColor(newColor);
}

void GUIObject::alignText(){
	text.setOrigin(0,0);
	hover_text.setOrigin(0,0);
	click_text.setOrigin(0,0);
	text.setPosition(sf::Vector2f(position.x, position.y));
	hover_text.setPosition(sf::Vector2f(hover_position.x, hover_position.y));
	click_text.setPosition(sf::Vector2f(click_position.x, click_position.y));
}

void GUIObject::centerText(){
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin((int)(textRect.left + textRect.width/2.0f),
				   (int)(textRect.top  + textRect.height/2.0f));
	hover_text.setOrigin((int)(textRect.left + textRect.width/2.0f),
				   (int)(textRect.top  + textRect.height/2.0f));
	click_text.setOrigin((int)(textRect.left + textRect.width/2.0f),
				   (int)(textRect.top  + textRect.height/2.0f));
	text.setPosition(sf::Vector2f(position.x + size.x/2 , position.y + size.y/2));
	hover_text.setPosition(sf::Vector2f(hover_position.x + hover_size.x/2 , hover_position.y + hover_size.y/2));
	click_text.setPosition(sf::Vector2f(click_position.x + click_size.x/2 , click_position.y + click_size.y/2));
}

void GUIObject::setFont(const sf::Font &new_font){
	font = new_font;
}

sf::Font GUIObject::getFont(){
	return font;
}

void GUIObject::setName(const std::string &new_name){
	text.setString(new_name);
	hover_text.setString(new_name);
	click_text.setString(new_name);
	centerText();
}