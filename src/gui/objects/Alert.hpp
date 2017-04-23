#ifndef ALERT_H
#define ALERT_H

#include "../GUIObject.hpp"

class Alert : public GUIObject{
	public:
		float fade;
		Alert();
		Alert(const std::string &);
		void set(const std::string &);
		bool click(const sf::Vector2i);
		void hover(const sf::Vector2i);
		void animate(float);
};

#endif