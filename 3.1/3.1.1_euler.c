#include<iostream>

using namespace std;

double f(double x){
	return x;
}

int main(){
	
	//parameters
	double x0 = 1.0;
	double t0 = 0.0;
	double tmax = 6.0;
	double dt = 0.2;
	
	//integration
	double x = x0;
	for(double t = t0; t < tmax; t = t+dt){
		x = x + f(x)*dt;
		cout << t << ", " << x << endl;
	}
	
	return 0;
	
}



