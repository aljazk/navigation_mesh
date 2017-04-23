#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include <SFML/Graphics.hpp>
#include "../draw/VertQuad.hpp"


class GUIObject{
	protected:
		int mode;
		sf::Font font;
	public:
		sf::Vector2f texture_position, hover_texture_position, click_texture_position; 
		sf::Vector2f texture_size, hover_texture_size, click_texture_size;
		// maybe it should be position[3]; (position[mode])
		sf::Vector2f position, hover_position, click_position;
		sf::Vector2f size, hover_size, click_size;
		sf::Color color, hover_color, click_color;
		unsigned int border_width, hover_border_width, click_border_width;
		sf::Color border_color, hover_border_color, click_border_color;
		sf::Text text, hover_text, click_text;
		std::string action;
		
		GUIObject();
		virtual void getVert(sf::VertexArray&);
		virtual void getText(sf::Text&);
		virtual void animate(float);
		virtual void hover(const sf::Vector2i);
		virtual bool click(const sf::Vector2i);
		virtual void addChar(const char);
		
		void setTexturePosition(const sf::Vector2f);
		void setTextureSize(const sf::Vector2f);
		
		void setPosition(const sf::Vector2f);
		void setSize(const sf::Vector2f);
		void setColor(const sf::Color);
		
		void setBorderWidth(const int);
		void setBorderColor(const sf::Color);
		
		void setText(const sf::Text &);
		void setTextColor(const sf::Color);
		void alignText();
		void centerText();
		
		void setFont(const sf::Font &);
		sf::Font getFont();
		
		void setName(const std::string &);
		
};

#endif