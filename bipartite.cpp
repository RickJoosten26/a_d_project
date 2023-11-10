#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


//class box
class Box {
	public: 
		double dim1, dim2, dim3;
		vector<Box> boxesInside; 

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



int max_amount_of_matches(vector<Box> left_perm, vector<Box> right_perm){
	
}



int main(){

	int size;
    cin >> size;

    vector<Box> start;

    for (int i = 0; i < size; i++){
        double dim1, dim2, dim3;
        cin >> dim1 >> dim2 >> dim3;
        start.push_back(Box(dim1, dim2, dim3));
    }

    vector<Box> end = start;

    

	return 0;
}