#include "Astar.hpp"

using namespace nm;

Astar::Astar(){

}

std::vector<unsigned int> Astar::run(std::vector<Node> &nodes, unsigned int start, unsigned int end){
	//copy all nodes so they dont change
	std::vector<Path> paths;
	paths.push_back(Path());
	paths[0].move(start, 0, nodes[start], nodes[end]);
	for(int h=0; h<1000000; h++){
		//order by weight
		//find the one with the smalles cost + heurstic
		unsigned int min_weight = 0;
		unsigned int min_id = 0;
		for(unsigned int i=0; i<paths.size(); i++){
			if((paths[i].weight < min_weight || min_weight == 0) && !paths[i].dead){
				min_weight = paths[i].weight;
				min_id = i;
			}
		}
		//std::cout << "step: " << h << "\ncurrent paths: " << paths.size() << "\npicked path: " << min_id << "\nweight: " << min_weight << std::endl;
		unsigned int current_node_id = paths[min_id].current();
		std::vector<unsigned int> neighbour_nodes = nodes[current_node_id].getNeighbors();
		unsigned int smalles_weight_neighbor = nodes[current_node_id].getSmallesWeightNeighbor(nodes[end]);
		bool dead = true;
		for(unsigned int i=0; i<neighbour_nodes.size(); i++){
			if(neighbour_nodes[i] != smalles_weight_neighbor){
				if(!nodes[neighbour_nodes[i]].taken){
					nodes[neighbour_nodes[i]].taken = true;
					dead = false;
					unsigned int cost = nodes[current_node_id].getNeighborCost(neighbour_nodes[i]);
					paths.push_back(paths[min_id]);
					paths[paths.size()-1].move(neighbour_nodes[i], cost, nodes[neighbour_nodes[i]], nodes[end]);
					//std::cout << min_weight << std::endl;
					if(paths[paths.size()-1].current() == end){
						//reset nodes before returning
						for(unsigned int i=0; i<nodes.size(); i++){
							nodes[i].taken = false;
						}
						return paths[paths.size()-1].getPath();
					}
				}
			}
		}
		if(!nodes[smalles_weight_neighbor].taken){
			nodes[smalles_weight_neighbor].taken = true;
			dead = false;
			unsigned int cost = nodes[current_node_id].getNeighborCost(smalles_weight_neighbor);
			paths[min_id].move(smalles_weight_neighbor, cost, nodes[smalles_weight_neighbor], nodes[end]);
			//std::cout << min_weight << std::endl;
			if(paths[min_id].current() == end){
				//reset nodes before returning
				for(unsigned int i=0; i<nodes.size(); i++){
					nodes[i].taken = false;
				}
				return paths[min_id].getPath();
			}
		}
		if(dead){
			paths[min_id].dead = true;
		}
		/*
		unsigned int next = nodes[paths[min_id].current()].getSmallesWeightNeighbor(nodes[end]);
		unsigned int cost = nodes[paths[min_id].current()].getNeighborCost(next);
		paths[min_id].move(next, cost, nodes[next], nodes[end]);
		//std::cout << min_weight << std::endl;
		if(paths[min_id].current() == end) return paths[min_id].getPath();
		*/
	}
	std::vector<unsigned int> c;
	return c;
}

std::vector<unsigned int> Astar::run(std::vector<Node> &nodes, unsigned int start, unsigned int end, sf::RenderWindow &window){
	std::vector<Path> paths;
	paths.push_back(Path());
	paths[0].move(start, 0, nodes[start], nodes[end]);
	sf::VertexArray quad(sf::Quads);
	for(int h=0; h<1000000; h++){
		//order by weight
		//find the one with the smalles cost + heurstic
		unsigned int min_weight = 0;
		unsigned int min_id = 0;
		for(unsigned int i=0; i<paths.size(); i++){
			if((paths[i].weight < min_weight || min_weight == 0) && !paths[i].dead){
				min_weight = paths[i].weight;
				min_id = i;
			}
		}
		//std::cout << "step: " << h << "\ncurrent paths: " << paths.size() << "\npicked path: " << min_id << "\nweight: " << min_weight << std::endl;
		unsigned int current_node_id = paths[min_id].current();
		std::vector<unsigned int> neighbour_nodes = nodes[current_node_id].getNeighbors();
		unsigned int smalles_weight_neighbor = nodes[current_node_id].getSmallesWeightNeighbor(nodes[end]);
		bool dead = true;
		for(unsigned int i=0; i<neighbour_nodes.size(); i++){
			if(neighbour_nodes[i] != smalles_weight_neighbor){
				if(!nodes[neighbour_nodes[i]].taken){
					nodes[neighbour_nodes[i]].taken = true;
					dead = false;
					unsigned int cost = nodes[current_node_id].getNeighborCost(neighbour_nodes[i]);
					paths.push_back(paths[min_id]);
					paths[paths.size()-1].move(neighbour_nodes[i], cost, nodes[neighbour_nodes[i]], nodes[end]);
					int cx,cy;
					nodes[neighbour_nodes[i]].getCenter(cx,cy);
					quad.append(sf::Vector2f(cx-5,cy-5));
					quad.append(sf::Vector2f(cx-5,cy+5));
					quad.append(sf::Vector2f(cx+5,cy+5));
					quad.append(sf::Vector2f(cx+5,cy-5));
					//std::cout << min_weight << std::endl;
					if(paths[paths.size()-1].current() == end) return paths[paths.size()-1].getPath();
				}
			}
		}
		if(!nodes[smalles_weight_neighbor].taken){
			nodes[smalles_weight_neighbor].taken = true;
			dead = false;
			unsigned int cost = nodes[current_node_id].getNeighborCost(smalles_weight_neighbor);
			paths[min_id].move(smalles_weight_neighbor, cost, nodes[smalles_weight_neighbor], nodes[end]);
			int cx,cy;
			nodes[smalles_weight_neighbor].getCenter(cx,cy);
			quad.append(sf::Vector2f(cx-5,cy-5));
			quad.append(sf::Vector2f(cx-5,cy+5));
			quad.append(sf::Vector2f(cx+5,cy+5));
			quad.append(sf::Vector2f(cx+5,cy-5));
			//std::cout << min_weight << std::endl;
			if(paths[min_id].current() == end) return paths[min_id].getPath();
		}
		if(dead){
			int cx,cy;
			paths[min_id].dead = true;
			nodes[current_node_id].getCenter(cx,cy);
			quad.append(sf::Vector2f(cx-5,cy-5));
			quad[quad.getVertexCount()-1].color = sf::Color::Red;
			quad.append(sf::Vector2f(cx-5,cy+5));
			quad[quad.getVertexCount()-1].color = sf::Color::Red;
			quad.append(sf::Vector2f(cx+5,cy+5));
			quad[quad.getVertexCount()-1].color = sf::Color::Red;
			quad.append(sf::Vector2f(cx+5,cy-5));
			quad[quad.getVertexCount()-1].color = sf::Color::Red;
		} else {
			int cx,cy;
			nodes[current_node_id].getCenter(cx,cy);
			quad.append(sf::Vector2f(cx-5,cy-5));
			quad[quad.getVertexCount()-1].color = sf::Color::Green;
			quad.append(sf::Vector2f(cx-5,cy+5));
			quad[quad.getVertexCount()-1].color = sf::Color::Green;
			quad.append(sf::Vector2f(cx+5,cy+5));
			quad[quad.getVertexCount()-1].color = sf::Color::Green;
			quad.append(sf::Vector2f(cx+5,cy-5));
			quad[quad.getVertexCount()-1].color = sf::Color::Green;
		}
		window.draw(quad);
		window.display();
		/*
		unsigned int next = nodes[paths[min_id].current()].getSmallesWeightNeighbor(nodes[end]);
		unsigned int cost = nodes[paths[min_id].current()].getNeighborCost(next);
		paths[min_id].move(next, cost, nodes[next], nodes[end]);
		//std::cout << min_weight << std::endl;
		if(paths[min_id].current() == end) return paths[min_id].getPath();
		*/
	}
	std::vector<unsigned int> c;
	return c;
}