#include <iostream>
#include <vector>
#include <fstream>
#include "Search_Based_Planners/dijkstra.h"
#include "Search_Based_Planners/Astar.hpp"
// #include "Search_Based_Planners/graph_construct.h"
//using namespace std;
#include <chrono>
using namespace std::chrono;

const int OBST_COST = 9;
const int INTERVAL =10;

int main() {
	int m,n;
	std::ifstream in("input.txt");
	in>>m>>n;
	std::vector< std::vector<int> > input(m);
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			int temp;
			// char bekar;
			in>>temp;
			// in>>bekar;
			if(temp==0){
				temp = 2;
			}else{
				temp = OBST_COST;
			}
			// std::cout<<temp;
			input[i].push_back(temp);
		}
	}
	
	int sx,sy,ex,ey;
	in>>sx>>sy>>ex>>ey;

	in.close();

	auto start = high_resolution_clock::now();

	Dijkstra Planner(input,m,n);
	Planner.plan(sx,sy,ey,ex);
	std::vector<std::pair<int,int> > path = Planner.get_path();

	for(int i=0;i<path.size();i++){
		input[path[i].first][path[i].second] = 5;
	}

	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);

  
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			std::cout<<input[i][j]<<" ";
		}
		std::cout<<std::endl;
	}


    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << std::endl;
         
	return 0;
	
}