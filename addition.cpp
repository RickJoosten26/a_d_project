#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){

	long long size;
	cin >> size;

	long long result = 0; 
	long long  n;
	
	for(int i = 0; i < size; i++){
		 
		cin >> n; 
		result += n; 
	}
	cout << result << endl;
	return 0;
}