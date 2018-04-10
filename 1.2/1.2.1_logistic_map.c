#include<iostream>

using namespace std;

int main(){
	
	double r = 2.6; //try also: 2.95, 3.14, 3.5, 3.7
	
	double x = 0.5;
	for(int n = 0; n < 100; ++n){
		cout << x << endl;
		x = r*x*(1-x);
	}
	
	return 0;
	
}
