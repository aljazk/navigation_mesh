#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <vector>
#include <memory>

#include "GUIObject.hpp"

#include "objects/Button.hpp"
#include "objects/Text.hpp"
#include "objects/Alert.hpp"
#include "objects/Input.hpp"
#include "objects/TexturedButton.hpp"

class GUI{
		std::vector<std::unique_ptr<GUIObject>> objects;
		bool mouse_down;
		int check_click;
		sf::Texture gui_texture;
	public:
		GUI();
		void add(std::unique_ptr<GUIObject> obj) { // use like GUI.add(std::unique_ptr<GUIObject>(new GUIObject(5)));
			objects.push_back(std::move(obj));
		}
		template <class T, class... Args>
		T& emplace(Args&&... args) { // use like GUIObject& A = GUI.emplace<GUIObject>(8);
			T* obj = new T(args...);
			objects.push_back(std::move(std::unique_ptr<T>(obj)));
			return *obj;
		}
		template <class T, class... Args>
		const T& emplace(Args&&... args) const {
			T* obj = new T(args...);
			objects.push_back(std::move(std::unique_ptr<T>(obj)));
			return *obj;
		}
		void loadTexture(const std::string &);
		void clear();
		std::string check(const sf::RenderWindow&);
		void draw(sf::RenderWindow &);
		void draw(sf::RenderWindow &, const float);
		void enterText(const sf::Event &);
};


#endif