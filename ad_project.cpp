#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

//class box
class Box {
	public: 
		double dim1, dim2, dim3;

		Box(double dimi1, double dimi2, double dimi3){
			dim1 = dimi1;
			dim2 = dimi2;
			dim3 = dimi3;
		}

	bool operator>(Box const& obj) 
    {  
	    return (dim1 > obj.dim1) && (dim2 > obj.dim2) && (dim3 > obj.dim3); 
    } 

	bool operator!=(Box const& obj)
	{
		return (dim1 != obj.dim1) && (dim2 != obj.dim2) && (dim3 != obj.dim3); 
	}

		bool operator>=(Box const& obj) 
    {  
	    return (dim1 >= obj.dim1) && (dim2 >= obj.dim2) && (dim3 >= obj.dim3); 
    } 

	void print() { cout << dim1 << "," << dim2 << "," << dim3 << endl; } 

};

bool operator<(Box a, Box b){
	return (a.dim1 <= b.dim1) && (a.dim2 <= b.dim2) && (a.dim3 <= b.dim3); 
}

bool fits (Box old, Box newB){
	return old >= newB;
}

bool fits_in_smaller (Box b, vector<Box> boxes){
	for(int i = 0; i < boxes.size(); i++){
		if(fits(boxes.at(i), b)){
			boxes.erase(boxes.begin() + i);
			boxes.push_back(b);
			return true;
		}
	}
	return false;
}

int smaller_one_fits (Box b, vector<Box> boxes, int amount){
	for(int i = 0; i < boxes.size(); i++){
		if(fits(b, boxes.at(i))){
			b = boxes.at(i);
			boxes.erase(boxes.begin() + i);
			amount++;
			return smaller_one_fits(b, boxes, amount);
		}
	}
	return amount;
}


int nr_of_boxes(vector<Box> boxes, vector<Box> stored){

	for (int i = 0; i < boxes.size(); i++){
		cout << boxes.size() << endl;
		Box current_box = boxes.at(boxes.size() - i);
		if(!stored.empty()){
			cout << "mayve\n";
			for(int j = stored.size() - 1; j > 0; j--){
				if(fits(stored.at(j), current_box)){
					cout << "yes\n";
					stored.erase(stored.begin() + j);
					stored.push_back(current_box);
				}
			}
		}
		else{
			stored.push_back(current_box);
		}
	}
	return stored.size();
}

int main(){
	int size;
	cin >> size;

	int min_amount_boxes = size;
	vector<Box> stored_boxes;
	vector<Box> boxes;
	for (int i = 0; i < size; i++){
		double dim1, dim2, dim3;
		cin >> dim1 >> dim2 >> dim3;
		boxes.push_back(Box(dim1, dim2, dim3));
	}
	sort(boxes.begin(), boxes.end());
	

	sort(boxes.begin(), boxes.end());
	cout << "The boxes are:/n" << endl;
	for(int i = 0; i < boxes.size(); i++){
		boxes.at(i).print();
	}

	min_amount_boxes = nr_of_boxes(boxes, stored_boxes);
	
	cout << min_amount_boxes << endl;
	return 0;
}
