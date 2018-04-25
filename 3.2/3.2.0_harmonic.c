#include<iostream>

using namespace std;

double fx(double y){
	return y;
}
double fy(double x){
	return -x;
}

void integrator(double *x, double *y, double dt){
	double kx1 = fx(*y);
	double ky1 = fy(*x);
	double kx2 = fx(*y + ky1*dt/2.0);
	double ky2 = fy(*x + kx1*dt/2.0);
	double kx3 = fx(*y + ky2*dt/2.0);
	double ky3 = fy(*x + kx2*dt/2.0);
	double kx4 = fx(*y + ky3*dt);
	double ky4 = fy(*x + kx3*dt);
	*x = *x + (kx1+2*kx2+2*kx3+kx4)*dt/6.0;
	*y = *y + (ky1+2*ky2+2*ky3+ky4)*dt/6.0;
}

int main(){
	
	//parameters
	double x0 = 1.0;
	double y0 = 1.0;
	double t0 = 0.0;
	double tmax = 10.0;
	double dt = 0.1;
	
	//integration
	double x = x0;
	double y = y0;
	for(double t = t0; t < tmax; t = t+dt){
		integrator(&x, &y, dt);
		cout << x << ", " << y << endl;
	}
	
	return 0;
	
}



