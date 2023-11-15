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
		//Constructor of a box, we immediately permute the dimensions such that dim1 > dim2 > dim3
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

//If a matching for box b is possible, this function returns true.
bool matching(vector<vector<bool>>& graph, int b, vector<bool>& seen, vector<int>& matchR){
	//Try every box on the right
	for(int v = 0; v < size; v++){
		//If box b fits in box v and v has not yet been seen, then visit v
		if(graph.at(b).at(v) && !seen.at(v)){
			seen.at(v) = true;
			//If box v has not stored another box yet or the box stored in v has another box in which it can fit, then store b in v.
			if(matchR.at(v) < 0 || matching(graph, matchR.at(v), seen, matchR)){
				matchR.at(v) = b;
				return true;
			}
		}
	}
	return false;
}

//A function that given a graph returns the maximum matching in this graph.
int max_matching(vector<vector<bool>>& graph){
	//This vector keeps track of the boxes that are already stored in a box on the right, i.e. matchR.at(b) is the box on the left
	//stored in box b. Initially no box stored another box so the value is -1.
	vector<int> matchR(size, -1);

	int result = 0;	
	for(int b = 0; b < size; b++){
		//For every box, every box on the right is initialized to not seen.
		vector<bool> seen(size, false);
		//If the current box can be stored, the matching increments.
		if(matching(graph, b, seen, matchR)){
			result++;
		}
	}
	return result;
}

int main(){
	//Input the size
	cin >> size;
	
    vector<Box> original_boxes;

	//All input boxes added to a vector with boxes
    for (int i = 0; i < size; i++){
        double dim1, dim2, dim3;
        cin >> dim1 >> dim2 >> dim3;
        original_boxes.push_back(Box(dim1, dim2, dim3));
    }

	//Sort the vector to speed up matching process
	sort(original_boxes.begin(), original_boxes.end());

	//Create a 2dimensional graph of boolean values all initialized to false
	vector<vector<bool>> graph(size, vector<bool>(size, false));

	//Update the value in the graph to true if a box on the left fits in a box on the right, setting the value to true and
	//creating a vertex between the 2 boxes.
	for(int i = 0; i < original_boxes.size(); i++){
		for(int j = 0; j < original_boxes.size(); j++){
			bool canStore = fits(original_boxes.at(i), original_boxes.at(j));
			graph.at(i).at(j) = canStore;
		}
	}
	//The max matching returns the amount of matches, so the final result is the size minus the boxed stored in another box.
	int result = size - max_matching(graph);
	cout << result << endl;
	return 0;
}