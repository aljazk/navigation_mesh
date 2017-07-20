#include "Node.hpp"

using namespace nm;

Node::Node(){
	taken = false;
	debug_color = sf::Color(255,0,0,50);
	debug_color_links = sf::Color(0,255,0,25);
}

Node::Node(const std::vector<int> &x, const std::vector<int> &y) : Node(){
	set(x, y);
}

void Node::clear(){
	x.clear();
	y.clear();
}

void Node::set(const std::vector<int> &x, const std::vector<int> &y){
	clear();
	unsigned int size = x.size();
	for(unsigned int i=0; i<size; i++){
		this->x.push_back(x[i]);
		this->y.push_back(y[i]);
	}
}

bool Node::addNeighbor(const unsigned int id, const unsigned int dist){
	unsigned int size = neighbor.size();
	for(unsigned int i=0; i<size; i++){
		if(neighbor[i] == id) return false;
	}
	neighbor.push_back(id);
	cost.push_back(dist);
	return true;
}

void Node::addNeighbor(Node &n, const unsigned int id){
	unsigned int s1 = x.size();
	unsigned int s2 = n.x.size();
	bool two = false;
	for(unsigned int i=0; i<s1; i++){
		for(unsigned int j=0; j<s2; j++){
			if (x[i] == n.x[j] && y[i] == n.y[j]){
				two = !two;
				if(!two){
					int cx, cy;
					int tcx, tcy;
					getCenter(tcx, tcy);
					n.getCenter(cx, cy);
					nx.push_back(cx);
					ny.push_back(cy);
					unsigned int dist = sqrt(pow(tcx-cx, 2) + pow(tcy-cy, 2));
					if(addNeighbor(id, dist)){
						neig.push_back(std::make_shared<Node>(n));
					}
				}
			}
		}
	}
}

void Node::add(const int x, const int y){
	this->x.push_back(x);
	this->y.push_back(y);
}

void Node::getVert(sf::VertexArray &vert){
	vert.append(sf::Vector2f(x[0], y[0]));
	vert[vert.getVertexCount()-1].color = sf::Color::Transparent;
	unsigned int size = x.size();
	for(unsigned int i=0; i<size; i++){
		vert.append(sf::Vector2f(x[i], y[i]));
		vert[vert.getVertexCount()-1].color = debug_color;
	}
	vert.append(sf::Vector2f(x[0], y[0]));
	vert[vert.getVertexCount()-1].color = debug_color;
	vert.append(sf::Vector2f(x[0], y[0]));
	vert[vert.getVertexCount()-1].color = sf::Color::Transparent;
}

void Node::getVertWithLinks(sf::VertexArray &vert){
	vert.append(sf::Vector2f(x[0], y[0]));
	vert[vert.getVertexCount()-1].color = sf::Color::Transparent;
	unsigned int size = x.size();
	for(unsigned int i=0; i<size; i++){
		vert.append(sf::Vector2f(x[i], y[i]));
		vert[vert.getVertexCount()-1].color = debug_color;
	}
	vert.append(sf::Vector2f(x[0], y[0]));
	vert[vert.getVertexCount()-1].color = debug_color;
	vert.append(sf::Vector2f(x[0], y[0]));
	vert[vert.getVertexCount()-1].color = sf::Color::Transparent;
	int cx, cy;
	getCenter(cx, cy);
	size = neighbor.size();
	for(unsigned int i=0; i<size; i++){
		vert.append(sf::Vector2f(cx, cy));
		vert[vert.getVertexCount()-1].color = sf::Color::Transparent;
		vert.append(sf::Vector2f(cx, cy));
		vert[vert.getVertexCount()-1].color = debug_color_links;
		vert.append(sf::Vector2f(nx[i], ny[i]));
		vert[vert.getVertexCount()-1].color = debug_color_links;
		vert.append(sf::Vector2f(nx[i], ny[i]));
		vert[vert.getVertexCount()-1].color = sf::Color::Transparent;
	}
}

void Node::getCenter(int &x, int &y){
	int fx = 0, fy = 0;
	unsigned int size = this->x.size();
	for(unsigned int i=0; i<size; i++){
		fx += this->x[i];
		fy += this->y[i];
	}
	x = fx / size;
	y = fy / size;
}

unsigned int Node::getSize(){
	return x.size();
}

unsigned int Node::getH(Node &n){
	int cx, cy;
	int tcx, tcy;
	getCenter(tcx, tcy);
	n.getCenter(cx, cy);
	return sqrt(pow(tcx-cx, 2) + pow(tcy-cy, 2));
}

unsigned int Node::getSmallesWeightNeighbor(Node &end_node){
	unsigned int min = 0;
	unsigned int min_id = 0;
	for(unsigned int i=0; i<neighbor.size(); i++){
		int tcx, tcy;
		end_node.getCenter(tcx, tcy);
		unsigned int dist = sqrt(pow(tcx-nx[i], 2) + pow(tcy-ny[i], 2));
		//std::cout << dist+cost[i] << std::endl;
		if(dist+cost[i] < min || min == 0){
			min = dist+cost[i];
			min_id = neighbor[i];
		}
	}
	//std::cout << "r: " << min << std::endl;
	return min_id;
}

unsigned int Node::getNeighborCost(const unsigned int id){
	for(unsigned int i=0; i<neighbor.size(); i++){
		if (neighbor[i] == id) return cost[i];
	}
	return 0;
}

void Node::getPoints(std::vector<int> &x, std::vector<int> &y){
	x = this->x;
	y = this->y;
}

void Node::getLR(int &lx, int &ly, int &rx, int &ry, const unsigned int next){
	unsigned int nid;
	unsigned int size = neighbor.size();
	for(unsigned int i=0; i<size; i++){
		if(neighbor[i] == next){
			nid = i;
			break;
		}
	}
	std::vector<int> nx;
	std::vector<int> ny;
	neig[nid]->getPoints(nx, ny);
	
	size = x.size();
	unsigned int sizen = nx.size();
	unsigned int p1, p2;
	bool one_set = false;
	for(unsigned int i=0; i<size; i++){
		for(unsigned int j=0; j<sizen; j++){
			if (x[i] == nx[j] && y[i] == ny[j]){
				if(!one_set){
					p1 = i;
					one_set = true;
				} else {
					p2 = i;
					break;
				}
			}
		}
	}
	if (p1 == p2-1){
		lx = x[p1];
		ly = y[p1];
		rx = x[p2];
		ry =  y[p2];
	} else {
		lx = x[p2];
		ly = y[p2];
		rx = x[p1];
		ry =  y[p1];
	}
}