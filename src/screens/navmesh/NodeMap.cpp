#include "NodeMap.hpp"

using namespace nm;

NodeMap::NodeMap(){
	Node n;
	unsigned int size_x = 248/5, size_y = 140/5;
	unsigned int dotsx[size_x][size_y];
	unsigned int dotsy[size_x][size_y];
	unsigned int size = 5*5;
	for(unsigned int i=0; i<size_x; i++){
		for(unsigned int j=0; j<size_y; j++){
			dotsx[i][j] = i*size + (rand()%21+10);
			dotsy[i][j] = j*size + (rand()%21+10);
			//std::cout << i << " " << j << std::endl;
			//std::cout << i*size << " " << j*size << std::endl;
		}
	}
	for(unsigned int i=0; i<size_x-1; i++){
		for(unsigned int j=0; j<size_y-1; j++){
			n.clear();
			n.add(dotsx[i][j], dotsy[i][j]);
			n.add(dotsx[i+1][j], dotsy[i+1][j]);
			n.add(dotsx[i+1][j+1], dotsy[i+1][j+1]);
			n.add(dotsx[i][j+1], dotsy[i][j+1]);
			nodes.push_back(n);
		}
	}
	
	/*
	for(unsigned int i=0; i<90; i++){
		for(unsigned int j=0; j<60; j++){
			if (i!=70 || j>50 || j<20){
				if (j!=50 || i>70 || i<50){
					n.clear();
					unsigned int size = 10;
					n.add(100+i*size, 100+j*size);
					n.add(100+size+i*size, 100+j*size);
					n.add(100+size+i*size, 100+size+j*size);
					n.add(100+i*size, 100+size+j*size);
					nodes.push_back(n);
				}
			}
		}
	}
	*/
	findNeighbors();
}

void NodeMap::findNeighbors(){
	unsigned int size = nodes.size();
	for(unsigned int i=0; i<size; i++){
		for(unsigned int j=0; j<size; j++){
			if(i != j) nodes[i].addNeighbor(nodes[j], j);
		}
		if (i%100 == 0) std::cout << i << " of " << size << std::endl;
	} 
}

void makeSquere(sf::VertexArray& vert, int x, int y, int size){
	sf::Vertex v;
	v.color = sf::Color::Blue;
	v.position.x = x;
	v.position.y = y-size;
	vert.append(v);
	v.position.x = x+size;
	v.position.y = y;
	vert.append(v);
	v.position.x = x;
	v.position.y = y+size;
	vert.append(v);
	v.position.x = x-size;
	v.position.y = y;
	vert.append(v);
	v.position.x = x-size;
	v.position.y = y;
	vert.append(v);
}

void NodeMap::getPath(std::vector<int> &path_x, std::vector<int> &path_y){
	unsigned int size = nodes.size();
	//std::cin.ignore();
	//get shortest path
	unsigned int start_node = 0, end_node = nodes.size()-1;
	std::vector<unsigned int> path = Astar::run(nodes, start_node, end_node);
	
	//get left and right points of the path
	size = path.size();
	std::vector<int> left_point_x, left_point_y;
	std::vector<int> right_point_x, right_point_y;
	unsigned int left_point_size = 0, right_point_size = 0;
	for(unsigned int i=0; i<size-1; i++){
		if(i != size){
			int lx, ly, rx, ry;
			nodes[path[i]].getLR(lx, ly, rx, ry, path[i+1]);
			//if point isnt the same as last one add it to points
			if (left_point_size == 0 || (left_point_x[left_point_size-1] != lx || left_point_y[left_point_size-1] != ly)){
				left_point_x.push_back(lx); left_point_y.push_back(ly);
				left_point_size++;
			}
			if (right_point_size == 0 || (right_point_x[right_point_size-1] != rx || right_point_y[right_point_size-1] != ry)){
				right_point_x.push_back(rx); right_point_y.push_back(ry);
				right_point_size++;
			}
		}
	}
	
	//smooth the path-------
	//create path and input starting location
	path_x.push_back(0); path_y.push_back(0);
	nodes[start_node].getCenter(path_x[0], path_y[0]);
	
	//create and calculate left and right angle
	float left_angle, right_angle;
	unsigned int points_size = left_point_x.size(), path_size = path_x.size();
	if (right_point_x.size() < points_size) points_size = right_point_x.size();
	left_angle = atan2(path_y[path_size-1] - left_point_y[0], left_point_x[0] - path_x[path_size-1]);
	right_angle = atan2(path_y[path_size-1] - right_point_y[0], right_point_x[0] - path_x[path_size-1]);
	float diff = left_angle - right_angle;
	while(diff < -atan(1)*4){
		diff += atan(1)*8;
	}
	
	//smooth out the path
	unsigned int left_i = 1, right_i = 1;
	unsigned int last_left_i = left_i, last_right_i = right_i;
	float new_diff = 0;
	//move left and right
	//if move makes angle wider, keep moving in that way, just stop changing last valid point
	//if angles intracept, move path to the last vaild point of the oposite side
	float min_left_angle = left_angle;
	float min_right_angle = right_angle;
	for(unsigned int i=1; i<points_size; i++){
		//calculate left angle
		left_angle = atan2(path_y[path_size-1] - left_point_y[left_i], left_point_x[left_i] - path_x[path_size-1]);
		new_diff = left_angle - min_right_angle;
		while(new_diff < -atan(1)*4){
			new_diff += atan(1)*8;
			
		}
		//if lines intracept
		if (new_diff < 0){
			left_i++;
			path_x.push_back(right_point_x[last_right_i]);
			path_y.push_back(right_point_y[last_right_i]);
			path_size++;
			diff = 0;
			left_i = last_right_i+1;
			right_i = last_right_i+1;
			last_left_i = left_i;
			last_right_i = right_i;
			i = left_i;
			min_left_angle = atan2(path_y[path_size-1] - left_point_y[left_i], left_point_x[left_i] - path_x[path_size-1]);
			min_right_angle = atan2(path_y[path_size-1] - right_point_y[right_i], right_point_x[right_i] - path_x[path_size-1]);
			diff = min_left_angle - min_right_angle;
			while(diff < -atan(1)*4){
				diff += atan(1)*8;
			}
		//if difference got smaller
		} else if(new_diff < diff){
			min_left_angle = left_angle;
			last_left_i = left_i;
			diff = new_diff;
		}
		left_i++;
		//std::cin.ignore();
		
		//calculate right angle
		right_angle = atan2(path_y[path_size-1] - right_point_y[right_i], right_point_x[right_i] - path_x[path_size-1]);
		new_diff = min_left_angle - right_angle;
		while(new_diff < -atan(1)*4){
			new_diff += atan(1)*8;
		}
		//if lines intracept
		if (new_diff < 0){
			right_i++;
			
			path_x.push_back(left_point_x[last_left_i]);
			path_y.push_back(left_point_y[last_left_i]);
			path_size++;
			diff = 0;
			left_i = last_left_i+1;
			right_i = last_left_i+1;
			last_left_i = left_i;
			last_right_i = right_i;
			i = left_i;
			min_left_angle = atan2(path_y[path_size-1] - left_point_y[left_i], left_point_x[left_i] - path_x[path_size-1]);
			min_right_angle = atan2(path_y[path_size-1] - right_point_y[right_i], right_point_x[right_i] - path_x[path_size-1]);
			diff = min_left_angle - min_right_angle;
			while(diff < -atan(1)*4){
				diff += atan(1)*8;
			}
		//if difference got smaller
		} else if(new_diff < diff){
			min_right_angle = right_angle;
			last_right_i = right_i;
			diff = new_diff;
		}
		right_i++;
	}
	//add end to the path
	path_x.push_back(0);
	path_y.push_back(0);
	nodes[end_node].getCenter(path_x[path_x.size()-1], path_y[path_x.size()-1]);
	path_size++;
}

void NodeMap::draw(sf::RenderWindow &window){
	sf::VertexArray vert(sf::LinesStrip);
	unsigned int size = nodes.size();
	for(unsigned int i=0; i<size; i++){
		nodes[i].getVertWithLinks(vert);
	}
	window.draw(vert);
	window.display();
	//std::cin.ignore();
	//get shortest path
	unsigned int start_node = 0, end_node = nodes.size()-1;
	std::vector<unsigned int> path = Astar::run(nodes, start_node, end_node);
	
	//get left and right points of the path
	int cx, cy;
	nodes[path[0]].getCenter(cx, cy);
	vert.append(sf::Vector2f(cx, cy));
	vert[vert.getVertexCount()-1].color = sf::Color::Transparent;
	size = path.size();
	sf::VertexArray point(sf::Lines);
	std::vector<int> left_point_x, left_point_y;
	std::vector<int> right_point_x, right_point_y;
	unsigned int left_point_size = 0, right_point_size = 0;
	for(unsigned int i=0; i<size-1; i++){
		int cx, cy;
		nodes[path[i]].getCenter(cx, cy);
		//std::cout << path[i] << std::endl;
		vert.append(sf::Vector2f(cx, cy));
		vert[vert.getVertexCount()-1].color = sf::Color::Blue;
		if(i != size){
			int lx, ly, rx, ry;
			nodes[path[i]].getLR(lx, ly, rx, ry, path[i+1]);
			//if point isnt the same as last one add it to points
			if (left_point_size == 0 || (left_point_x[left_point_size-1] != lx || left_point_y[left_point_size-1] != ly)){
				left_point_x.push_back(lx); left_point_y.push_back(ly);
				left_point_size++;
				point.append(sf::Vector2f(lx, ly));
				point[point.getVertexCount()-1].color = sf::Color(0,255,0);
				point.append(sf::Vector2f(lx, ly+3));
				point[point.getVertexCount()-1].color = sf::Color(0,255,0);
			}
			if (right_point_size == 0 || (right_point_x[right_point_size-1] != rx || right_point_y[right_point_size-1] != ry)){
				right_point_x.push_back(rx); right_point_y.push_back(ry);
				right_point_size++;
				point.append(sf::Vector2f(rx, ry));
				point[point.getVertexCount()-1].color = sf::Color(0,0,255);
				point.append(sf::Vector2f(rx, ry+3));
				point[point.getVertexCount()-1].color = sf::Color(0,0,255);
			}
		}
	}
	std::cout << "done" << std::endl;
	//add end to vertexarray
	nodes[path[size-1]].getCenter(cx, cy);
	vert.append(sf::Vector2f(cx, cy));
	vert[vert.getVertexCount()-1].color = sf::Color::Transparent;
	
	
	//smooth the path-------
	//create path and input starting location
	std::vector<int> path_x, path_y;
	path_x.push_back(0); path_y.push_back(0);
	nodes[start_node].getCenter(path_x[0], path_y[0]);
	//draw start of the path
	vert.append(sf::Vector2f(path_x[0], path_y[0]));
	vert[vert.getVertexCount()-1].color = sf::Color::Transparent;
	vert.append(sf::Vector2f(path_x[0], path_y[0]));
	vert[vert.getVertexCount()-1].color = sf::Color::Magenta;
	
	//debug drawing
	sf::VertexArray debug_vert(sf::LinesStrip);
	sf::VertexArray angle_lines(sf::Lines);
	//create and calculate left and right angle
	float left_angle, right_angle;
	unsigned int points_size = left_point_x.size(), path_size = path_x.size();
	if (right_point_x.size() < points_size) points_size = right_point_x.size();
	left_angle = atan2(path_y[path_size-1] - left_point_y[0], left_point_x[0] - path_x[path_size-1]);
	right_angle = atan2(path_y[path_size-1] - right_point_y[0], right_point_x[0] - path_x[path_size-1]);
	float diff = left_angle - right_angle;
	while(diff < -atan(1)*4){
		diff += atan(1)*8;
	}
	// std::cout << "ly: " << path_y[path_size-1] - left_point_y[0] << " rx: " << path_x[path_size-1] - left_point_x[0] << std::endl;
	// std::cout << "start: " << left_angle << " " << right_angle << " diff: " << diff << std::endl;
	
	makeSquere(debug_vert, path_x[path_size-1], path_y[path_size-1], 10);
	sf::Vertex line_v;
	line_v.color = sf::Color(255,100,0);
	line_v.position.x = path_x[path_size-1];
	line_v.position.y = path_y[path_size-1];
	angle_lines.append(line_v);
	line_v.color = sf::Color(255,100,0);
	line_v.position.x = left_point_x[0];
	line_v.position.y = left_point_y[0];
	angle_lines.append(line_v);
	line_v.color = sf::Color::Yellow;
	line_v.position.x = path_x[path_size-1];
	line_v.position.y = path_y[path_size-1];
	angle_lines.append(line_v);
	line_v.color = sf::Color::Yellow;
	line_v.position.x = right_point_x[0];
	line_v.position.y = right_point_y[0];
	angle_lines.append(line_v);
	
	std::cout << "start smoothing" << std::endl;
	std::cout << atan2(0,-1) << " " << atan2(1,0) << " " << atan2(0,1) << " " << atan2(-2,0) << " " << atan2(-2, -2) << std::endl;
	unsigned int left_i = 1, right_i = 1;
	unsigned int last_left_i = left_i, last_right_i = right_i;
	float new_diff = 0;
	sf::Color draw_color;
	//move left and right
	//if move makes angle wider, keep moving in that way, just stop changing last valid point
	//if angles intracept, move path to the last vaild point of the oposite side
	float min_left_angle = left_angle;
	float min_right_angle = right_angle;
	for(unsigned int i=1; i<points_size; i++){
		//calculations are wrong too.. alogrithm is bullshit
		
		/*
		last_min;
		move_left();
		if (new_diff < diff){
			last_min = left_point();
			diff = new_diff;
		} else if (new_diff < 0){
			//paths crossed
		}
		*/
		//same for right side
		
		
		//calculate left angle
		left_angle = atan2(path_y[path_size-1] - left_point_y[left_i], left_point_x[left_i] - path_x[path_size-1]);
		new_diff = left_angle - min_right_angle;
		while(new_diff < -atan(1)*4){
			new_diff += atan(1)*8;
			
		}
		draw_color = sf::Color(255,100,0);
		std::cout << "Move left diff: " << new_diff << " old: " << diff << std::endl;
		//if lines intracept
		if (new_diff < 0){
			draw_color = sf::Color::White;
			line_v.color = draw_color;
			line_v.position.x = path_x[path_size-1];
			line_v.position.y = path_y[path_size-1];
			angle_lines.append(line_v);
			line_v.color = draw_color;
			line_v.position.x = left_point_x[left_i];
			line_v.position.y = left_point_y[left_i];
			angle_lines.append(line_v);
			left_i++;
			window.clear(sf::Color::Black);
			window.draw(vert);
			window.draw(point);
			window.draw(debug_vert);
			window.draw(angle_lines);
			window.display();
			//std::cin.ignore();
			
			draw_color = sf::Color(255,100,0);
			path_x.push_back(right_point_x[last_right_i]);
			path_y.push_back(right_point_y[last_right_i]);
			path_size++;
			diff = 0;
			left_i = last_right_i+1;
			right_i = last_right_i+1;
			last_left_i = left_i;
			last_right_i = right_i;
			i = left_i;
			min_left_angle = atan2(path_y[path_size-1] - left_point_y[left_i], left_point_x[left_i] - path_x[path_size-1]);
			min_right_angle = atan2(path_y[path_size-1] - right_point_y[right_i], right_point_x[right_i] - path_x[path_size-1]);
			diff = min_left_angle - min_right_angle;
			while(diff < -atan(1)*4){
				diff += atan(1)*8;
			}
			makeSquere(debug_vert, path_x[path_size-1], path_y[path_size-1], 10);
		//if difference got smaller
		} else if(new_diff < diff){
			min_left_angle = left_angle;
			last_left_i = left_i;
			diff = new_diff;
		//if difference got bigger
		} else if (new_diff > diff){
			draw_color = sf::Color::Red;
		}
		line_v.color = draw_color;
		line_v.position.x = path_x[path_size-1];
		line_v.position.y = path_y[path_size-1];
		angle_lines.append(line_v);
		line_v.color = draw_color;
		line_v.position.x = left_point_x[left_i];
		line_v.position.y = left_point_y[left_i];
		angle_lines.append(line_v);
		left_i++;
		window.clear(sf::Color::Black);
		window.draw(vert);
		window.draw(point);
		window.draw(debug_vert);
		window.draw(angle_lines);
		window.display();
		//std::cin.ignore();
		
		right_angle = atan2(path_y[path_size-1] - right_point_y[right_i], right_point_x[right_i] - path_x[path_size-1]);
		new_diff = min_left_angle - right_angle;
		while(new_diff < -atan(1)*4){
			new_diff += atan(1)*8;
		}
		draw_color = sf::Color::Yellow;
		std::cout << "Move right diff: " << new_diff << " old: " << diff << std::endl;
		//if lines intracept
		if (new_diff < 0){
			draw_color = sf::Color::White;
			line_v.color = draw_color;
			line_v.position.x = path_x[path_size-1];
			line_v.position.y = path_y[path_size-1];
			angle_lines.append(line_v);
			line_v.color = draw_color;
			line_v.position.x = right_point_x[right_i];
			line_v.position.y = right_point_y[right_i];
			angle_lines.append(line_v);
			right_i++;
			window.clear(sf::Color::Black);
			window.draw(vert);
			window.draw(point);
			window.draw(debug_vert);
			window.draw(angle_lines);
			window.display();
			//std::cin.ignore();
			
			draw_color = sf::Color::Yellow;
			path_x.push_back(left_point_x[last_left_i]);
			path_y.push_back(left_point_y[last_left_i]);
			path_size++;
			diff = 0;
			left_i = last_left_i+1;
			right_i = last_left_i+1;
			last_left_i = left_i;
			last_right_i = right_i;
			i = left_i;
			min_left_angle = atan2(path_y[path_size-1] - left_point_y[left_i], left_point_x[left_i] - path_x[path_size-1]);
			min_right_angle = atan2(path_y[path_size-1] - right_point_y[right_i], right_point_x[right_i] - path_x[path_size-1]);
			diff = min_left_angle - min_right_angle;
			while(diff < -atan(1)*4){
				diff += atan(1)*8;
			}
			makeSquere(debug_vert, path_x[path_size-1], path_y[path_size-1], 10);
		//if difference got smaller
		} else if(new_diff < diff){
			min_right_angle = right_angle;
			last_right_i = right_i;
			diff = new_diff;
		//angle got wider
		} else if (new_diff > diff){
			draw_color = sf::Color::Red;
		}
		line_v.color = draw_color;
		line_v.position.x = path_x[path_size-1];
		line_v.position.y = path_y[path_size-1];
		angle_lines.append(line_v);
		line_v.color = draw_color;
		line_v.position.x = right_point_x[right_i];
		line_v.position.y = right_point_y[right_i];
		angle_lines.append(line_v);
		right_i++;
		window.clear(sf::Color::Black);
		window.draw(vert);
		window.draw(point);
		window.draw(debug_vert);
		window.draw(angle_lines);
		window.display();
		//std::cin.ignore();
	}
	//add end to the path
	std::cout << "Adding last node" << std::endl;
	path_x.push_back(0);
	path_y.push_back(0);
	nodes[end_node].getCenter(path_x[path_x.size()-1], path_y[path_x.size()-1]);
	path_size++;
	std::cout << "drawing path" << std::endl;
	//draw path
	sf::VertexArray vpath(sf::LinesStrip);
	for(unsigned int i=0; i<path_x.size(); i++){
		sf::Vertex v(sf::Vector2f(path_x[i], path_y[i]));
		v.color = sf::Color::White;
		vpath.append(v);
	}
	// std::cout << "add end vertex" << std::endl;
	// //add end to vertexarray
	// nodes[path[size-1]].getCenter(cx, cy);
	// vpath.append(sf::Vector2f(cx, cy));
	// vpath[vert.getVertexCount()-1].color = sf::Color::White;
	std::cout << "draw everything" << std::endl;
	window.clear(sf::Color::Black);
	window.draw(vert);
	window.draw(point);
	window.draw(vpath);
	window.display();
	std::cout << "Done" << std::endl;
	std::cin.ignore();
}