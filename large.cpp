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



Box smallestFitBinary(vector<Box> unassignedBox, Box b, int boxAt){

	return b; 
}



Box biggestFit(vector<Box> unassignedBox, Box b, int boxAt){
	
	cout << "Checking box "; 
	b.print(); 
	cout << endl;
	 

	if (boxAt == unassignedBox.size()-1){
		return b; 
	}

	for (int i = boxAt-1; i > 0; i--){

		
		cout << "Now checking box " << i << " :";
		unassignedBox.at(i).print(); 
		cout << endl;
	

		if (unassignedBox.at(i) < b){
			cout << "Found it!\n"; 
			return unassignedBox.at(i); 
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

	vector<Box> unassignedBox; 
	vector<Box> finalBox; 
	
	for(int i = 0; i < size; i++){
		double dim1, dim2, dim3;
		cin >> dim1 >> dim2 >> dim3;
		Box b = Box(dim1, dim2, dim3); 
		unassignedBox.push_back(b); 

	}

    //Sort 
	sort(unassignedBox.begin(), unassignedBox.end());
	vector<Box> toCheckBox = unassignedBox; 

	
	cout << endl << "Sorted vector is: \n"; 
	printV(unassignedBox); 
	cout << endl; 
	

	int boxesStored = 0; 
	int boxesNeeded = 0; 

	int j = 1;  
	
	while (!unassignedBox.empty() && j < unassignedBox.size()){
		cout << j << endl; 
		Box parent = unassignedBox.at(unassignedBox.size()-j); 
		cout << "Parent box is ";
		parent.print(); 
		cout << endl; 


		Box child = biggestFit(toCheckBox, parent, j);
		if (child != parent){
			unassignedBox.erase(remove(unassignedBox.begin(), unassignedBox.end(), child), unassignedBox.end()); 
            toCheckBox.erase(remove(toCheckBox.begin(), toCheckBox.end(),child), toCheckBox.end()); 
			toCheckBox.erase(remove(toCheckBox.begin(), toCheckBox.end(), child), toCheckBox.end()); 

			parent.boxesInside.push_back(child); 
			finalBox.push_back(parent); 
			boxesStored++; 
			j--; 
			
			cout << "Child is: "; 
			child.print();
			cout << endl; 
			
		}		
		j++; 
		cout << j << endl; 

	
	}
	printV(finalBox); 

	cout << "\nResult is: " << size - boxesStored << endl;
	 
	//als je dit leest trek een bak

    // ik ben blind 
    //sorry cout << handgebaar("trek") + handgebaar("een") + handgebaar("bak") << endl;


    // "handgebaar("trek")" - vrij gay tbh vo

	// infite loop got me like xD 

    //Hype
	return 0;
}