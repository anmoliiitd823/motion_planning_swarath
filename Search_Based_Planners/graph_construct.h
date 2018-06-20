/*
	Dependencies: vector
*/

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
		cumulative_cost = 100000;
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

class Graph {
	std::vector<Node>  **adjacency_list;

public:
	void MatrixToGraph(std::vector<std::vector<int> > &matrix,int height,int width){
		adjacency_list = new std::vector<Node>* [height];

		for(int i=0;i<width;i++){
			adjacency_list[i] = new std::vector<Node>[width];
		}

		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				Node x(i,j,matrix[i][j]);

				//First Node in the adjacency list in is the node itself 
				// adjacency_list[i][j].push_back(x);

				//Straight paths
				if(i>0){
					x.set_edge_weight(1);
					adjacency_list[i-1][j].push_back(x);
				}
				if(j>0){
					x.set_edge_weight(1);
					adjacency_list[i][j-1].push_back(x);
				}
				if(j<width-1){
					x.set_edge_weight(1);
					adjacency_list[i][j+1].push_back(x);
				}
				if(i<height-1){
					x.set_edge_weight(1);
					adjacency_list[i+1][j].push_back(x);
				}

				
				if(i>0){
					if(j>0){
						x.set_edge_weight(10);
						adjacency_list[i-1][j-1].push_back(x);
					}
					if(j<width-1){
						x.set_edge_weight(10);
						adjacency_list[i-1][j+1].push_back(x);
					}
				}

				if(i<height-1){
					if(j>0){
						x.set_edge_weight(10);
						adjacency_list[i+1][j-1].push_back(x);
					}
					if(j<width-1){
						x.set_edge_weight(10);
						adjacency_list[i+1][j+1].push_back(x);
					}
				}

				

			}
		}
	}

	std::vector<Node>** get_adjacency_list(){
		return adjacency_list;
	}
};