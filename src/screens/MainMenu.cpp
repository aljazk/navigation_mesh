#include "MainMenu.hpp"

MainMenu::MainMenu(){
	// create font
	font.loadFromFile("arial.ttf");
	// create text
	text.setFont(font);
	// define eclipsed time
	eclipsed = 1;
	// create interface
	createGUI();
}

void MainMenu::createGUI(){
	int startPos = 50;
	int sizeY = 30;
	int gap = 4;
	Button mbutton;
	mbutton.setPosition(sf::Vector2f(10,startPos+(sizeY+gap)*0));
	mbutton.setName("Start");
	mbutton.action = "sp";
	gui.emplace<Button>(mbutton);
	mbutton.setPosition(sf::Vector2f(10,startPos+(sizeY+gap)*1));
	mbutton.setName("Slow");
	mbutton.action = "me";
	gui.emplace<Button>(mbutton);
	mbutton.setPosition(sf::Vector2f(10,startPos+(sizeY+gap)*2));
	mbutton.setName("Exit");
	mbutton.action = "exit";
	gui.emplace<Button>(mbutton);
}

std::vector<Vertex> genPoints(unsigned int count, unsigned int x, unsigned int y){
	std::vector<Vertex> dots;
	for(unsigned int i=0; i<count; i++){
		dots.push_back(Vertex(rand() % x, rand() % y));
	}
	return dots;
}

void MainMenu::run(sf::RenderWindow &window){
	std::string action = "";
	// start loop
	//nm::NodeMap nm(window);
	std::vector<Vertex> points = genPoints(20, window.getSize().x, window.getSize().y);
	Triangulate::triangulate(points, window);
	
    while (window.isOpen()){
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)){
			//inter.enterText(event);
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
		}
		
		// clear window
        window.clear(sf::Color::Black);
		
		action = gui.check(window);
		if(action == "exit"){
            window.close();
		}
		
		std::vector<int> path_x;
		std::vector<int> path_y;
		//nm.draw(window);
		//nm.getPath(path_x, path_y);
		//nm::NodeMap::drawPath(path_x, path_y, window);
		
		//gui.draw(window);
		// end the current frame
		eclipsed = clock.restart().asSeconds();
		// display fps
		std::ostringstream s;
		s << 1.f/eclipsed << std::endl;
		text.setString(s.str());
		text.setCharacterSize(10);
		text.setFillColor(sf::Color::White);
		text.setPosition(10,10);
		window.draw(text);

		// draw stuff on window
        window.display();
        //wait();
    }
}