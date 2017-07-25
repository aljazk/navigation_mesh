#include "Triangulate.hpp"

Triangulate::Triangulate(){

}

unsigned int findMin(const std::vector<Vertex> &dots){
	Vertex min(INT_MAX,INT_MAX);
	const unsigned int size = dots.size();
	unsigned int min_id = size;
	for(unsigned int i=0; i<size; i++){
		if(dots[i].x < min.x){
			min = dots[i];
			min_id = i;
		} else if (dots[i].x == min.x && dots[i].y < min.y){
			min = dots[i];
			min_id = i;
		}
	}
	return min_id;
}

float dist(const Vertex p1, const Vertex p2){
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}


unsigned int findClose(const std::vector<Vertex> &dots, Edge &e, bool &found){
	unsigned int close_id = 0;
	float min_dist = FLT_MAX;
	unsigned int size = dots.size();
	found = false;
	for(unsigned int i=0; i<size; i++){
		if(e.checkSide(dots[i])){
			float sdist = 0;
			Vertex p1 = e.getPoint1();
			Vertex p2 = e.getPoint2();
			sdist += dist(dots[i], p1);
			sdist += dist(dots[i], p2);
			if(sdist < min_dist && sdist != dist(p1, p2)){
				found = true;
				min_dist = sdist;
				close_id = i;
			}
		}
	}
	return close_id;
}

unsigned int findClose(const std::vector<Vertex> &dots, Edge &e){
	bool found;
	return findClose(dots, e, found);
}

unsigned int findClose(const std::vector<Vertex> &dots, unsigned int id){
	unsigned int close_id = id;
	unsigned int min_dist = INT_MAX;
	unsigned int size = dots.size();
	for(unsigned int i=0; i<size; i++){
		if(i != id){
			unsigned int sdist = dist(dots[i], dots[id]);
			if(sdist < min_dist){
				min_dist = sdist;
				close_id = i;
			}
		}
	}
	return close_id;
}

Triangle firstTriangle(const std::vector<Vertex> &dots){
	if(dots.size() < 3){
		std::cout << "Not enought points to form a triangle" << std::endl;
		return Triangle();
	}
	unsigned int start = findMin(dots);
	unsigned int closest = findClose(dots, start);
	Edge e(dots[start], dots[closest]);
	bool found = false;
	unsigned int last = findClose(dots, e, found);
	if(!found){
		e = Edge(dots[closest], dots[start]);
		last = findClose(dots, e, found);
		if(!found){
			std::cout << "Cannot create first triangle" << std::endl;
			return Triangle();
		}
	}
	std::vector<Vertex> points;
	points.push_back(dots[start]);
	points.push_back(dots[closest]);
	points.push_back(dots[last]);
	return Triangle(points);
}

void drawTriangles(sf::RenderWindow &window, std::vector<Triangle> &tri){
	sf::VertexArray v(sf::Lines);
	for(unsigned int i=0; i<tri.size(); i++){
		tri[i].getVert(v);
	}
	window.draw(v);
}

void drawDots(sf::RenderWindow &window, std::vector<Vertex> &dots){
	sf::VertexArray v(sf::Points);
	for(unsigned int i=0; i<dots.size(); i++){
		v.append(sf::Vector2f(dots[i].x, dots[i].y));
		v[i].color = sf::Color::Green;
	}
	window.draw(v);
}

std::vector<std::shared_ptr<Edge>> getAllOpenEdges(const std::vector<Triangle> &t){
		std::vector<std::shared_ptr<Edge>> e;
		for(unsigned int i=0; i<t.size(); i++){
			std::vector<std::shared_ptr<Edge>> e1 = t[i].getOpenEdges();
			for(unsigned int j=0; j<e1.size(); i++){
				e.push_back(e1[i]);
			}
		}
		return e;
}

std::vector<Triangle> Triangulate::triangulate(const std::vector<Vertex> &dots){
	std::vector<Triangle> t;
	t.push_back(firstTriangle(dots));
	while(true){
		std::vector<std::shared_ptr<Edge>> e = getAllOpenEdges(t);
		if(e.size() == 0){
			break;
		} else {
			//cuntinue here.. vector of edges can be more dynamic..
		}
	}
	return t;
}

std::vector<Triangle> Triangulate::triangulate(std::vector<Vertex> &dots, sf::RenderWindow &window){
	std::vector<Triangle> t = triangulate(dots);
	drawTriangles(window, t);
	drawDots(window, dots);
	window.display();
	std::cin.ignore();
	return t;
}