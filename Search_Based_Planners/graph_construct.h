/*
	Dependencies: vector
*/
#include <chrono>
using namespace std::chrono;
class Vertex{

	int state_cost;
	int x;
	int y;

public:

	Vertex(int x,int y,int state_cost){
		this->x = x;
		this->y = y;
		this->state_cost = state_cost;
	}

	int get_x(){
		return x;
	}		

	int get_y(){
		return y;
	}

	int get_state_cost(){
		return state_cost;
	}

	void add_to_state_cost(int state_cost){
		this->state_cost = state_cost;
		return;
	}

};

class Node{

	Vertex* vertex;
	int edge_weight;

public:

	int cumulative_cost;

	Node(int x,int y,int state_cost,int edge_weight = 0){
		vertex = new Vertex(x,y,state_cost);
		this->edge_weight = edge_weight;
		cumulative_cost = INT_MAX;
	}
	Node(){

	}

	int get_edge_weight(){
		return edge_weight;
	}

	void set_edge_weight(int edge_weight){
		this->edge_weight = edge_weight;
	}

	Vertex* get_vertex() const{
		return vertex;
	}
};