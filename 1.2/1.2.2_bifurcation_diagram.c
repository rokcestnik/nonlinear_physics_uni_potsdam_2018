#include<iostream>

using namespace std;

int main(){
	
	//simpler
	double dr = 0.02;
	for(double r = 0; r < 4; r = r+dr){
		double x = 0.5;
		for(int n = 0; n < 100; ++n){
			x = r*x*(1-x);
		}
		cout << r << " " << x << endl;
	}
	
	//better
	/*
	double dx0 = 0.01;
	for(double x0 = dx0; x0 < 1; x0 = x0+dx0){
		double dr = 0.002;
		for(double r = 2.5; r < 4; r = r+dr){
			double x = x0;
			for(int n = 0; n < 400; ++n){
				x = r*x*(1-x);
			}
			cout << r << " " << x << endl;
		}
	}
	*/
	
	return 0;
	
}
