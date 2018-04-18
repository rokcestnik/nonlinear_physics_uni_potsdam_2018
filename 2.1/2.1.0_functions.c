#include<iostream>

using namespace std;

//function returning an integer
int function1(int x){
	return 2*x;
}

//function returning a float
double function2(double x, int n){
	double result = 1;
	for(int i = 0; i < n; ++i){
		result = result*x;
	}
	return result;
} 

//function not returning anything
void function3(int n){
	for(int i = 0; i < n; ++i){
		cout << "i = " << i << endl;
	}
} 

int main(){
	
	int a = function1(2);			//a = 6
	
	double b = function2(0.5, 3);	//b = 0.125 
	
	function3(5);
	
	return 0;
	
}

