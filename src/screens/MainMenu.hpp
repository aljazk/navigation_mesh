#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include "../gui/GUI.hpp"
#include <iostream>
#include <sstream>
#include "navmesh/NodeMap.hpp"


class MainMenu{
		sf::RenderWindow window;
		sf::Font font;
		sf::Text text;
		sf::Clock clock;
		float eclipsed;
		bool mouseDown, rightMouseDown;
		GUI gui;
		void createGUI();
    public:
		MainMenu();
		void run(sf::RenderWindow &);
};

#endif
