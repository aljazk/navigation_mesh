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


unsigned int findClose(const std::vector<Vertex> &dots, const Edge &e, bool &found){
	unsigned int close_id = 0;
	float min_dist = FLT_MAX;
	unsigned int size = dots.size();
	found = false;
	for(unsigned int i=0; i<size; i++){
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
	return close_id;
}

unsigned int findClose(const std::vector<Vertex> &dots, const Edge &e){
	bool found;
	return findClose(dots, e, found);
}

std::vector<Triangle> Triangulate::triangulate(const std::vector<Vertex> &points){
	std::vector<Triangle> t;
	return t;
}