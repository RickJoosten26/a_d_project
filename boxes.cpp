#include <iostream>
#include <fstream>
#include <vector>
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


int main(){
	int size;
	cin >> size;

	int min_amount_boxes = size;
	vector<Box> small_boxes;
	double dim1, dim2, dim3;
	cin >> dim1 >> dim2 >> dim3;
	
	Box biggest_box = Box(dim1, dim2, dim3);
	
	for(int i = 0; i < size - 1; i++){
		//cout << "min amount of boxes: " << min_amount_boxes << endl;
		//cout << "Biggest: "; biggest_box.print();
		double dimi1, dimi2, dimi3;
		cin >> dimi1 >> dimi2 >> dimi3;
		
		Box current_box = Box(dimi1, dimi2, dimi3);
		//cout << "Current: "; current_box.print();
		if (fits(biggest_box, current_box)){
			min_amount_boxes--;
			small_boxes.push_back(current_box);
			//cout << "I enter the first if" << endl;
		}
		else if (fits(current_box, biggest_box)){
			min_amount_boxes--;
			small_boxes.push_back(biggest_box);
			biggest_box = current_box;
			//cout << "I entered the second if" << endl;
		}
		else if (current_box > biggest_box){
			small_boxes.push_back(biggest_box);
			biggest_box = current_box;
			//cout << "I entered the third if" << endl;
		}
		else if (fits_in_smaller(current_box, small_boxes)){
			min_amount_boxes--;
			small_boxes.push_back(current_box);
			//cout << "I entered the fourth if" << endl;
		}
		else{
			small_boxes.push_back(current_box);
		}
	}
	cout << min_amount_boxes << endl;
	return 0;
}
