#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;


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
	return(a.dim1 < b.dim1) && (a.dim2 < b.dim2) && (a.dim3 < b.dim3);
}

int size = 0;



bool matching(vector<vector<bool>>& graph, int u, vector<bool>& seen, vector<int>& matchR, vector<vector<int>>& dp){
	for(int v = 0; v < size; v++){
		if(graph.at(u).at(v) && !seen.at(v)){
			seen.at(v) = true;
			if(matchR.at(v) < 0 || (dp.at(matchR.at(v)).at(u) != -1 && matching(graph, matchR.at(v), seen, matchR, dp))){
				matchR.at(v) = u;
                if(matchR.at(v) != -1){
                    dp.at(u).at(matchR.at(u)) = 1;
                }
				return true;
			}
		}
	}
    if(matchR.at(u) != -1){
        dp.at(u).at(matchR.at(u)) = 0;
    }
	return false;
}

int max_matching(vector<vector<bool>>& graph, vector<int>& matchR, vector<vector<int>>& dp){
	int result = 0;	

	for(int u = 0; u < size; u++){
		vector<bool> seen(size, false);
		if(matching(graph, u, seen, matchR, dp)){
			result++;
		}
	}
	return result;
}
int main(){

	clock_t startTime = clock();
	
	int temp;
    cin >> temp;
	size = temp;

    vector<int> matchR(size, -1);
    vector<vector<int>> dp(size, vector<int>(size, -1));
    
    vector<Box> original_boxes;

    for (int i = 0; i < size; i++){
        double dim1, dim2, dim3;
        cin >> dim1 >> dim2 >> dim3;
        original_boxes.push_back(Box(dim1, dim2, dim3));
    }

	sort(original_boxes.begin(), original_boxes.end());
	vector<vector<bool>> graph(size, vector<bool>(size, false));

	for(int i = 0; i < original_boxes.size(); i++){
		for(int j = 0; j < original_boxes.size(); j++){
			bool canStore = fits(original_boxes.at(i), original_boxes.at(j));
			graph.at(i).at(j) = canStore;
		}
	}
	int result = size - max_matching(graph, matchR, dp);
	cout << result << endl;
	cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
	return 0;
}