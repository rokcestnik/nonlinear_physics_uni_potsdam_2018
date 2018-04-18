#include<iostream>

using namespace std;

int main(){
	
	//integer array of size 3
	int arr[3]; 
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	
	//double array of size 20
	double arr2[20];
	arr2[0] = 0.67;
	for(int i = 1; i < 20; ++i){
		arr2[i] = arr2[i-1]*0.8;
	}
	
	//printing arrays
	for(int i = 0; i < 20; ++i){
		cout << "arr2[" << i << "] = " << arr2[i] << endl;
	}
	
	return 0;
	
}

