#ifndef PATH_H
#define PATH_H

#include "Node.hpp"
#include <vector>

namespace nm{

class Path{
		std::vector<unsigned int> ids;
	public:
		Path();
		bool dead;
		unsigned int cost;
		unsigned int weight;
		void move(const unsigned int, const unsigned int, Node &, Node &);
		unsigned int current(){ return ids[ids.size()-1]; }
		std::vector<unsigned int> getPath() { return ids; }
};

}

#endif