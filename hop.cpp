#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;

#define NIL 0
#define INF (1<<28)

//class box
class Box {
	public: 
		double dim1, dim2, dim3;

		Box(double dimi1, double dimi2, double dimi3){
			vector<double> dims = {dimi1, dimi2, dimi3}; 
			sort(dims.begin(), dims.end()); 
			dim1 = dims.at(2); 
			dim2 = dims.at(1); 
			dim3 = dims.at(0); 
		}

	bool operator>(Box const& obj) 
    {  
	    return (dim1 > obj.dim1) && (dim2 > obj.dim2) && (dim3 > obj.dim3); 
    } 

	bool operator!=(Box const& obj)
	{
		return (dim1 != obj.dim1) && (dim2 != obj.dim2) && (dim3 != obj.dim3); 
	}

	bool operator==(Box const& obj)
	{
		return (dim1 == obj.dim1) && (dim2 == obj.dim2) && (dim3 == obj.dim3); 
	}

		bool operator>=(Box const& obj) 
    {  
	    return (dim1 >= obj.dim1) && (dim2 >= obj.dim2) && (dim3 >= obj.dim3); 
    } 

};

bool operator<(Box a, Box b){
	return (a.dim1 < b.dim1); 
}


bool fits(Box a, Box b){
    return (a.dim1 < b.dim1 && a.dim2 < b.dim2 && a.dim3 < b.dim3);
}


int size = 0;

// ... Your Box class and other functions remain the same ...

// BFS function to build level graph and check if there is a path from source to sink
bool bfs(vector<vector<int>>& adj, vector<int>& level) {
    queue<int> Q;
    fill(level.begin(), level.end(), -1);
    level[0] = 0;
    Q.push(0);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int v : adj[u]) {
            if (level[v] < 0 && adj[u][v] > 0) {
                level[v] = level[u] + 1;
                Q.push(v);
            }
        }
    }
    return level[size] > 0;
}

// DFS to find blocking flow
int dfs(vector<vector<int>>& adj, vector<int>& level, vector<int>& start, int u, int flow) {
    if (u == size) return flow;
    while (start[u] < adj[u].size()) {
        int v = adj[u][start[u]];
        if (level[v] == level[u] + 1 && adj[u][v] > 0) {
            int curr_flow = min(flow, adj[u][v]);
            int temp_flow = dfs(adj, level, start, v, curr_flow);
            if (temp_flow > 0) {
                adj[u][v] -= temp_flow;
                adj[v][u] += temp_flow;
                return temp_flow;
            }
        }
        start[u]++;
    }
    return 0;
}

int max_matching(vector<vector<int>>& adj) {
    if (size == 0) return 0;
    int total = 0;
    vector<int> level(size + 1), start(size + 1);
    while (bfs(adj, level)) {
        fill(start.begin(), start.end(), 0);
        while (int flow = dfs(adj, level, start, 0, INF)) {
            total += flow;
        }
    }
    return total;
}



int main(){

	clock_t startTime = clock();
	
	int temp;
    cin >> temp;
	size = temp;

    vector<Box> original_boxes;

    for (int i = 0; i < size; i++){
        double dim1, dim2, dim3;
        cin >> dim1 >> dim2 >> dim3;
        original_boxes.push_back(Box(dim1, dim2, dim3));
    }

	sort(original_boxes.begin(), original_boxes.end());
    vector<vector<int>> adj(size);

    for(int i = 0; i < original_boxes.size(); i++){
        for(int j = 0; j < original_boxes.size(); j++){
            bool canStore = fits(original_boxes.at(i), original_boxes.at(j));
            if(canStore){
                adj.at(i).push_back(j);
            }
        }
    }
	int result = size - max_matching(adj);
	cout << result << endl;
	cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
	return 0;
}