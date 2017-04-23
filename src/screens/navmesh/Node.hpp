#ifndef NODE_H
#define NODE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <memory>

namespace nm{

class Node{
		std::vector<int> x;
		std::vector<int> y;
		std::vector<std::shared_ptr<Node>> neig;
		std::vector<unsigned int> neighbor;
		std::vector<unsigned int> cost;
		std::vector<int> nx;
		std::vector<int> ny;
	public:
		bool taken;
		Node();
		Node(const std::vector<int> &, const std::vector<int> &);
		void clear();
		void set(const std::vector<int> &, const std::vector<int> &);
		bool addNeighbor(const unsigned int, const unsigned int);
		void addNeighbor(Node &, const unsigned int);
		std::vector<unsigned int> getNeighbors() { return neighbor; }
		void add(const int, const int);
		void getVert(sf::VertexArray &);
		void getVertWithLinks(sf::VertexArray &);
		void getCenter(int &, int &);
		unsigned int getH(Node &);
		unsigned int getSmallesWeightNeighbor(Node &end_node);
		unsigned int getNeighborCost(const unsigned int);
		void getPoints(std::vector<int> &, std::vector<int> &);
		void getLR(int &, int &, int &, int &, const unsigned int);
};

}

#endif