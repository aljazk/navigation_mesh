#ifndef TRIANGULATE_H
#define TRIANGULATE_H

#include <climits>
#include <cfloat>
#include <cmath>
#include "Triangle.hpp"

class Triangulate{

	public:
		Triangulate();
		static std::vector<Triangle> triangulate(const std::vector<Vertex> &);
		static std::vector<Triangle> triangulate(const Vertex *);
};

#endif