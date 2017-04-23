#ifndef INPUT_H
#define INPUT_H

#include "../GUIObject.hpp"

class Input : public GUIObject{
	public:
		Input();
		void hover(const sf::Vector2i);
		bool click(const sf::Vector2i);
};

#endif