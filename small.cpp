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



Box smallestFitBinary(vector<Box> uBox, Box b, int boxAt){

	return b; 
}


Box smallestFit(vector<Box> uBox, Box b, int boxAt){

	
	cout << "Checking box "; 
	b.print(); 
	cout << endl;
	

	if (boxAt == uBox.size()-1){
		return b; 
	}

	for (int i = boxAt+1; i < uBox.size(); i++){

		
		cout << "Now checking box " << i << " :";
		uBox.at(i).print(); 
		cout << endl;
		

		if (uBox.at(i) > b && uBox.at(i) != b){
			cout << "Found it!\n"; 
			return uBox.at(i); 
		}
	}
	return b; 
}

void printV(vector<Box> b){
	for (int i = 0; i < b.size(); i++){
		cout << "Box " << i << ": "; 
		b.at(i).print(); 
		cout << endl; 
	}
}



int main(){


    //Get input
	int size;
	cin >> size;

	vector<Box> uBox; 
	vector<Box> fBox; 
	
	for(int i = 0; i < size; i++){
		double dim1, dim2, dim3;
		cin >> dim1 >> dim2 >> dim3;
		Box b = Box(dim1, dim2, dim3); 
		uBox.push_back(b); 

	}

    //Sort 
	sort(uBox.begin(), uBox.end());
	vector<Box> aBox = uBox; 

	
	cout << endl << "Sorted vector is: \n"; 
	printV(uBox); 
	cout << endl; 
	

	int boxesStored = 0; 
	int boxesNeeded = 0; 

	int j = 0; 
	
	while (!uBox.empty() && j < uBox.size()){
		cout << j << endl; 
		Box currentBox = uBox.at(j); 
		cout << "Current box is ";
		currentBox.print(); 
		cout << endl; 


		Box parent = smallestFit(aBox, currentBox, j);
		if (parent != currentBox){
			uBox.erase(remove(uBox.begin(), uBox.end(), currentBox), uBox.end()); 
			aBox.erase(remove(aBox.begin(), aBox.end(), parent), aBox.end()); 

			parent.boxesInside.push_back(currentBox); 
			fBox.push_back(currentBox); 
			boxesStored++; 
			j--; 
			
			cout << "Parent is: "; 
			parent.print();
			cout << endl; 
			
		}		
		j++; 
		cout << j << endl; 

	
	}
	printV(fBox); 

	cout << "Result "<< size - boxesStored << endl;
	 
	




	
	return 0;
}