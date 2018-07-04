#include<iostream>

using namespace std;

//function taking a 2D array
void print_array(double **a, int n, int m){
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			cout << a[i][j] << ", ";
		}
		cout << endl;
	}
}

int main(void){
	
	//array dimensions
	int n = 5;
	int m = 10;
	//initializing a 2D array
	double **a;
	a = new double*[n];
	for(int i = 0; i < n; ++i){
		a[i] = new double[m];
	}
	//fill in the 2D array
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			a[i][j] = i+j;
		}
	}
	
	//function call
	print_array(a,n,m);
	
	return 0;
	
}
