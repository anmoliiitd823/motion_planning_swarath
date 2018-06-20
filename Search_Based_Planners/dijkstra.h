#include <queue>
#include <climits>
#include <cmath>
#include "graph_construct.h"


class mycomparison
{
	bool reverse;
public:
	mycomparison(const bool& revparam=true){
 		reverse=revparam;
	}
  	bool operator() (const Node lhs, const Node rhs) const
  	{
    	if (reverse) return (lhs.cumulative_cost>rhs.cumulative_cost);
    	else return (lhs.cumulative_cost<rhs.cumulative_cost);
  	}
};

class Dijkstra{
	Graph graph;
	bool** visited;
	std::pair<int,int>** predecessor;
	std::priority_queue<Node,std::vector<Node>,mycomparison> pq;
	std::vector<std::pair<int,int> > path;
	int** distance;

public:
	Dijkstra(std::vector<std::vector<int> > &matrix,int height,int width){
		graph.MatrixToGraph(matrix,height,width);
		visited = new bool*[height];
		predecessor = new std::pair<int,int>*[height];
		distance = new int*[height];
		for(int i=0;i<height;i++){
			visited[i] = new bool[width];
			predecessor[i] = new std::pair<int,int>[height];
			distance[i] = new int[height];
			for (int j = 0; j < width; ++j)
			{
				visited[i][j] = false;
				predecessor[i][j].first = -1;
				predecessor[i][j].second = -1;
				distance[i][j] = INT_MAX;
			}
		}
	}	

	void plan(int startx,int starty,int goalx,int goaly){
		std::vector<Node>** adjacency_list = graph.get_adjacency_list();
		std::vector<Node>* current = &adjacency_list[startx][starty];
		visited[startx][starty] = true;
		distance[startx][starty] = 0;
		int next = 0;
		int next_x = startx;
		int next_y = starty;

		do{
			for(int i=0;i<(*current).size();i++){
				int x = (*current)[i].get_vertex()->get_x();
				int y = (*current)[i].get_vertex()->get_y();
				
	            if (distance[x][y] > distance[next_x][next_y] + (*current)[i].get_vertex()->get_state_cost() + (*current)[i].get_edge_weight() + sqrt(pow(x-goalx,2)+pow(y-goaly,2)) && visited[x][y]==false)
	            {	

	                distance[x][y] = distance[next_x][next_y] + (*current)[i].get_vertex()->get_state_cost() + (*current)[i].get_edge_weight() + sqrt(pow(x-goalx,2)+pow(y-goaly,2));
	                (*current)[i].cumulative_cost = distance[x][y];

	                pq.push((*current)[i]);
	                predecessor[x][y].first = next_x;
					predecessor[x][y].second = next_y;
					visited[x][y] = true;

					// std::pair<int,int> z(x,y);

					// path.push_back(z);
	            }
				
			}
			Node x = pq.top();
			pq.pop();

			next = x.get_vertex()->get_state_cost();
			next_x = x.get_vertex()->get_x();
			next_y = x.get_vertex()->get_y();

			if(next_x==goalx && next_y==goaly){
				// break;
			}

			visited[next_x][next_y] = true;
			(*current).resize(0);
			current = &adjacency_list[next_x][next_y];

		}while(pq.size()!=0);

		next_x = goalx;
		next_y = goaly;

		while(predecessor[next_x][next_y].first != startx || predecessor[next_x][next_y].second != starty){

			int x = next_x,y = next_y;
			std::pair<int,int> z(predecessor[x][y].first,predecessor[x][y].second);

			path.push_back(z);

			next_x = predecessor[x][y].first;
			next_y = predecessor[x][y].second;

		}


	}

	std::vector<std::pair<int,int> > get_path(){
		return path;
	}
};