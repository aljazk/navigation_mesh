#include "GUI.hpp"

GUI::GUI(){
	check_click = -1;
	//loadTexture("images/button.png");
}

void GUI::loadTexture(const std::string &t_string){
	if (!gui_texture.loadFromFile(t_string)){
		std::cout << "Cannot load texture from: " << t_string << "\n";
	}
}

void GUI::clear(){
	//std::cout << objects.size() << " objects removed from gui\n";
	objects.clear();
}

std::string GUI::check(const sf::RenderWindow &window){
	const sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
	
	std::string action = "";
	//check if mouse hovers a object
	if(check_click == -1){
		for(unsigned int i=0; i<objects.size(); i++){
			objects[i]->hover(mouse_position);
		}
		
		//check if mouse clicked a object
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if(!mouse_down){
				for(unsigned int i=0; i<objects.size(); i++){
					if (objects[i]->click(mouse_position)){
						//std::cout << "Entering check click mode\n";
						check_click = i;
					}
				}
			}
			mouse_down = true;
		} else {
			mouse_down = false;
		}
	} else {
		if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if (objects[check_click]->click(mouse_position)){
				//std::cout << "Object clicked! \n";
				action = objects[check_click]->action;
				check_click = -1;
			} else {
				//std::cout << "Leaving check click mode\n";
				check_click = -1;
			}
		}
	}
	
	return action;
}

void GUI::draw(sf::RenderWindow &window){
	//draw object texture
	sf::VertexArray vertex;
	vertex.setPrimitiveType(sf::Quads);
	
	for(unsigned int i=0; i<objects.size(); i++){
		objects[i]->animate(1);
		objects[i]->getVert(vertex);
	}
	window.draw(vertex, &gui_texture);
	
	//draw object text
	sf::Text text;
	for(unsigned int i=0; i<objects.size(); i++){
		objects[i]->getText(text);
		sf::Font font = objects[i]->getFont();
		text.setFont(font);
		window.draw(text);
	}
}

void GUI::draw(sf::RenderWindow &window, const float eclipsed){
	//draw object texture
	sf::VertexArray vertex;
	vertex.setPrimitiveType(sf::Quads);
	
	for(unsigned int i=0; i<objects.size(); i++){
		objects[i]->animate(eclipsed);
		objects[i]->getVert(vertex);
	}
	//window.draw(vertex, &gui_texture);
	window.draw(vertex);
	
	//draw object text
	sf::Text text;
	for(unsigned int i=0; i<objects.size(); i++){
		objects[i]->getText(text);
		sf::Font font = objects[i]->getFont();
		text.setFont(font);
		window.draw(text);
	}
}

void GUI::enterText(const sf::Event &event){
	if (event.type == sf::Event::TextEntered){
		for(unsigned int i=0; i<objects.size(); i++){
			if (event.text.unicode < 128){
				objects[i]->addChar(event.text.unicode);
			}
		}
	}
}