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
  	bool operator() (const std::pair<std::pair<int,int>,int> lhs, std::pair<std::pair<int,int>,int> rhs) const
  	{
    	if (reverse) return (lhs.second>rhs.second);
    	else return (lhs.second<rhs.second);
  	}
};

class Dijkstra{
	bool** visited;
	std::pair<int,int>** predecessor;
	std::priority_queue<std::pair<std::pair<int,int>,int>,std::vector<std::pair<std::pair<int,int>,int> >,mycomparison> pq;
	std::vector<std::pair<int,int> > path;
	int** distance;
	std::vector<std::vector<int> > matrix;
	int** cumulative_cost;

public:
	Dijkstra(std::vector<std::vector<int> > &matrix,int height,int width){
		this->matrix = matrix;
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

	void step(int x,int y,int next_x,int next_y,int startx,int starty,int edge_weight,int m,int n){
		if(x<0 || y<0 || x>=m || y>=n){
			return;
		}
		int g = distance[next_x][next_y];
		int h = matrix[x][y] + edge_weight;

		int epsilon = 5;

        if (distance[x][y] > g + epsilon*h && visited[x][y]==false)
        {	

            distance[x][y] = g + epsilon*h;

            std::pair<std::pair<int,int>,int> z;

            z.first.first = x;
            z.first.second = y;

            z.second = distance[x][y];

            pq.push(z);
            predecessor[x][y].first = next_x;
			predecessor[x][y].second = next_y;
			visited[x][y] = true;

			// std::pair<int,int> z1(x,y);

			// path.push_back(z1);
        }
	}

	void plan(int startx,int starty,int goalx,int goaly){
		visited[startx][starty] = true;
		distance[startx][starty] = 0;
		int next = 0;
		int next_x = startx;
		int next_y = starty;

		do{
			int x,y;
			// std::cout<<"#"<<next_x<<" "<<next_y<<std::endl;
			x = next_x;
			y = next_y+1;	
			step(x,y,next_x,next_y,startx,starty,1,matrix.size(),matrix[0].size());

			x = next_x+1;
			y = next_y;	
			step(x,y,next_x,next_y,startx,starty,1,matrix.size(),matrix[0].size());

			x = next_x-1;
			y = next_y;	
			step(x,y,next_x,next_y,startx,starty,1,matrix.size(),matrix[0].size());

			x = next_x;
			y = next_y-1;	
			step(x,y,next_x,next_y,startx,starty,1,matrix.size(),matrix[0].size());

			x = next_x+1;
			y = next_y+1;	
			step(x,y,next_x,next_y,startx,starty,10,matrix.size(),matrix[0].size());

			x = next_x+1;
			y = next_y-1;	
			step(x,y,next_x,next_y,startx,starty,10,matrix.size(),matrix[0].size());

			x = next_x-1;
			y = next_y+1;	
			step(x,y,next_x,next_y,startx,starty,10,matrix.size(),matrix[0].size());

			x = next_x-1;
			y = next_y-1;	
			step(x,y,next_x,next_y,startx,starty,10,matrix.size(),matrix[0].size());
					
			


			std::pair<std::pair<int,int>,int> top = pq.top();
			pq.pop();

			// n =ext x.get_vertex()->get_state_cost(;
			next_x = top.first.first;
			next_y = top.first.second;

			if(next_x==goalx && next_y==goaly){
				break;
			}

			visited[next_x][next_y] = true;
			// (*current).resize(0);
			// current = &adjacency_list[next_x][next_y];

		}while(pq.size()!=0);

		next_x = goalx;
		next_y = goaly;

		std::cout<<distance[next_x][next_y]<<std::endl;

		while(predecessor[next_x][next_y].first != startx || predecessor[next_x][next_y].second != starty){

			int x = next_x;
			int y = next_y;
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