#include <iostream>
#include <vector>
using namespace std;

const int OBST_COST = 3000;

void print_path(int** dp,int si,int sj,int ei,int ej,int m,int n){
	if(si==ei && sj==ej){
		return;
	}
	if(sj>=n-1){
		return;
	}
	int option1 = dp[si][sj+1];
	int option2 = OBST_COST;
	if(si<m-1)
		option2 = dp[si+1][sj+1];
	int option3 = OBST_COST;
	if(si>=1)
		option3 = dp[si-1][sj+1];
	if(option1<option2 && option1<option3){
		cout<<si<<" "<<sj+1<<endl;
		print_path(dp,si,sj+1,ei,ej,m,n);
	}else if(option2<option1 && option2<option3){
		cout<<si+1<<" "<<sj+1<<endl;
		print_path(dp,si+1,sj+1,ei,ej,m,n);
	}else{
		cout<<si-1<<" "<<sj+1<<endl;
		print_path(dp,si-1,sj+1,ei,ej,m,n);
	}
}

int min_cost(vector< vector<int> > input, int si, int sj, int ei, int ej,int** dp,int m,int n) {
	if (si == ei && sj == ej) {
		return input[ei][ej];
	}
	if (si >= m || sj >= n || si<0 || sj<0) {
		return OBST_COST;
	}
	if(dp[si][sj]!=-1){
		return dp[si][sj];
	}
	int option1 = min_cost(input, si , sj + 1, ei, ej, dp, m, n);
	int option2 = min_cost(input, si + 1, sj + 1, ei, ej, dp, m, n);
	int option3 = min_cost(input, si - 1, sj + 1, ei, ej, dp, m, n);
	dp[si][sj] = input[si][sj] + min(option1, min(option2 , option3));
	return dp[si][sj];
}

int main() {
	int m,n;
	cin>>m>>n;
	vector< vector<int> > input(m);
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			int temp;
			cin>>temp;
			input[i].push_back(temp);
		}
	}
	int** dp = new int*[m];
	for(int i=0;i<n;i++){
		dp[i] = new int[n];
		for(int j=0;j<n;j++){
			dp[i][j] = -1;
		}
	}
	int sx,sy,ex,ey;
	cout<<"Enter Start X"<<endl;
	cin>>sx;
	cout<<"Enter Start Y"<<endl;
	cin>>sy;
	cout<<"Enter End X"<<endl;
	cin>>ex;
	cout<<"Enter End Y"<<endl;
	cin>>ey;
	cout << min_cost(input,sx,sy,ex,ey,dp,m,n) << endl;

	// for(int i=0;i<m;i++){
	// 	for(int j=0;j<n;j++){
	// 		cout<<dp[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }
	
	print_path(dp,sx,sy,ex,ey,m,n);
	for(int i=0;i<m;i++){
		delete [] dp[i];
	}
	delete [] dp;
}
