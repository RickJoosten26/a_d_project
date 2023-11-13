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

	void print() { cout << dim1 << "," << dim2 << "," << dim3;  } 

};

bool operator<(Box a, Box b){
	return (a.dim1 < b.dim1); 
}

bool fits(Box a, Box b){
	return(a.dim1 < b.dim1) && (a.dim2 < b.dim2) && (a.dim3 < b.dim3);
}
int size = 0;


bool matching(vector<vector<bool>>& graph, int u, vector<bool>& seen, vector<int>& matchR){
	for(int v = 0; v < size; v++){
		if(graph.at(u).at(v) && !seen.at(v)){
	//		cout << graph.at(u).at(v) << endl;
	//		cout << "first if: u = " << u << " v = " << v << endl;
			seen.at(v) = true;

			if(matchR.at(v) < 0 || matching(graph, matchR.at(v), seen, matchR)){
	//			cout << "matchR: "<< matchR.at(v) << endl;
	//			cout << "second if: u =" << u << " v = " << v << endl;
				matchR.at(v) = u;
				return true;
			}
		}
	}
	return false;
}

int max_matching(vector<vector<bool>>& graph){
	vector<int> matchR(size, -1);

	int result = 0;	

	for(int u = 0; u < size; u++){
		vector<bool> seen(size, false);

		if(matching(graph, u, seen, matchR)){
	//		cout << "I was true!" <<endl;
			result++;
		}
	}
	//cout << result << endl;
	return result;
}

int main(){

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

	vector<Box> copy = original_boxes;

	vector<vector<Box>> boxes = {{original_boxes} , {copy}};

	vector<vector<bool>> graph(size, vector<bool>(size, false));

	for(int i = 0; i < original_boxes.size(); i++){
		for(int j = 0; j < copy.size(); j++){
			if(fits(original_boxes.at(i), copy.at(j))){
				graph.at(i).at(j) = true;
			}
			else{
				graph.at(i).at(j) = false;
			}
		}
	}

	/*
	for(int i = 0; i < original_boxes.size(); i++){
		cout << "\n";
		for(int j = 0; j < copy.size(); j++){
			cout << graph.at(i).at(j);
		}
	}
	cout << "\n";
	*/


	int result = size - max_matching(graph);
	cout << result << endl;
	return 0;
}