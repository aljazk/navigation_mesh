#include "screens/MainMenu.hpp"
#include <iostream>

#define WINDOW_WIDTH (1280)
#define WINDOW_HEIGHT (720)

int main(){
	// create the window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window", sf::Style::Default, settings);
	window.setPosition(sf::Vector2i(500, 0));
	window.setVerticalSyncEnabled(false);
	//window.setFramerateLimit(120);
	//window.setKeyRepeatEnabled(false);
	std::cout << "Creating Main Manu" << std::endl;
	//start the game
	MainMenu mainMenu;
	std::cout << "To Main Manu" << std::endl;
	mainMenu.run(window);
    
    return 0;
}