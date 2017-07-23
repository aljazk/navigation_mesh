#include "Triangulate.hpp"

Triangulate::Triangulate(){

}

unsigned int findMin(const std::vector<Vertex> &dots, const unsigned int size){
	Vertex min(INT_MAX,INT_MAX);
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

std::vector<Triangle> Triangulate::triangulate(const std::vector<Vertex> &points){
	
}