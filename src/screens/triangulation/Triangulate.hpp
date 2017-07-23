#ifndef TRIANGULATE_H
#define TRIANGULATE_H

#include "Triangle.hpp"

class Triangulate{

	public:
		Triangulate();
		static std::vector<Triangle> triangulate(const std::vector<Vertex> &);
		static std::vector<Triangle> triangulate(const Vertex *);
};

#endif