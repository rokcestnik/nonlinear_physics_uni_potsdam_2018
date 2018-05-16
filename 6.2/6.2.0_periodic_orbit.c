#include<iostream>
#include<fstream>
#include<cmath>
#define Pi 3.14159

using namespace std;

double mu; 

double fx(double y){
	return y;
}
double fy(double x, double y){
	return mu*(1-x*x)*y - x;
}

void integrator(double *x, double *y, double dt){
	double kx1 = fx(*y);
	double ky1 = fy(*x, *y);
	double kx2 = fx(*y + ky1*dt/2.0);
	double ky2 = fy(*x + kx1*dt/2.0, *y + ky1*dt/2.0);
	double kx3 = fx(*y + ky2*dt/2.0);
	double ky3 = fy(*x + kx2*dt/2.0, *y + ky2*dt/2.0);
	double kx4 = fx(*y + ky3*dt);
	double ky4 = fy(*x + kx3*dt, *y + ky3*dt);
	*x = *x + (kx1+2*kx2+2*kx3+kx4)*dt/6.0;
	*y = *y + (ky1+2*ky2+2*ky3+ky4)*dt/6.0;
}

int main(){
	
	//parameters
	mu = 1.0;
	double range = 4;
	double t0 = 0.0;
	double tmax = 10.0;
	double dt = 0.01;
	
	//output files
	ofstream fout_xy("xy.dat");
	
	//integration
	for(double x0 = -range; x0 <= range; x0 += 0.5){
		cout << "x0 = " << x0 << endl;
		for(double y0 = -range; y0 <= range; y0 += 0.5){
			double x = x0;
			double y = y0;
			for(double t = t0; t < tmax; t = t+dt){
				integrator(&x, &y, dt);
				if(x == x && y == y) fout_xy << x << ", " << y << endl; //check if x or y are not "nan"
			}
			fout_xy << endl;
		}
	}
	
	return 0;
	
}



