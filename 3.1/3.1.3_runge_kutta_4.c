#include<iostream>

using namespace std;

double f(double x){
	return x;
}

void integrator(double *x, double dt){
	double k1 = f(*x);
	double k2 = f(*x + k1*dt/2.0);
	double k3 = f(*x + k2*dt/2.0);
	double k4 = f(*x + k3*dt);
	*x = *x + (k1+2*k2+2*k3+k4)*dt/6.0;
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
		integrator(&x, dt);
		cout << t << ", " << x << endl;
	}
	
	return 0;
	
}



