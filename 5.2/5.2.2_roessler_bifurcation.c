#include<iostream>
#include<cmath>

using namespace std;

double mu;

double fx(double y, double z){
	return -y-z;
}
double fy(double x, double y){
	return x+mu*y;
}
double fz(double x, double z){
	return 0.4+z*(x-8.5);
}

void integrator(double *x, double *y, double *z, double dt){
	double kx1 = fx(*y, *z);
	double ky1 = fy(*x, *y);
	double kz1 = fz(*x, *z);
	double kx2 = fx(*y + ky1*dt/2.0, *z + kz1*dt/2.0);
	double ky2 = fy(*x + kx1*dt/2.0, *y + ky1*dt/2.0);
	double kz2 = fz(*x + kx1*dt/2.0, *z + kz1*dt/2.0);
	double kx3 = fx(*y + ky2*dt/2.0, *z + kz2*dt/2.0);
	double ky3 = fy(*x + kx2*dt/2.0, *y + ky2*dt/2.0);
	double kz3 = fz(*x + kx2*dt/2.0, *z + kz2*dt/2.0);
	double kx4 = fx(*y + ky3*dt, *z + kz3*dt);
	double ky4 = fy(*x + kx3*dt, *y + ky3*dt);
	double kz4 = fz(*x + kx3*dt, *z + kz3*dt);
	*x = *x + (kx1+2*kx2+2*kx3+kx4)*dt/6.0;
	*y = *y + (ky1+2*ky2+2*ky3+ky4)*dt/6.0;
	*z = *z + (kz1+2*kz2+2*kz3+kz4)*dt/6.0;
}

int main(){
	
	//parameters
	double x0 = 5.0;
	double y0 = 5.0;
	double z0 = 1.0;
	double t0 = 0.0;
	double trelax = 500.0;
	double tmax = 1000.0;
	double dt = 0.05;
	
	for(mu = 0; mu < 0.2; mu = mu+0.001){
		//integration
		double x = x0;
		double y = y0;
		double z = z0;
		double xh; //history value for x
		for(double t = t0; t < trelax; t = t+dt){
			integrator(&x, &y, &z, dt);
		}
		for(double t = t0; t < tmax; t = t+dt){
			integrator(&x, &y, &z, dt);
			if(xh > 0 && x < 0){ //when x crossed zero
				cout << mu << ", " << y << endl;
			}
			//update z history
			xh = x;
		}
	}
	
	return 0;
	
}



