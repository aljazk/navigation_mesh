#ifndef TEXT_H
#define TEXT_H

#include "../GUIObject.hpp"

class Text : public GUIObject{
	public:
		Text();
		bool click(const sf::Vector2i);
};

#endif