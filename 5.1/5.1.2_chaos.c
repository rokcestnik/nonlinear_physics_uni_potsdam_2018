#include<iostream>
#include<cmath>

using namespace std;

double distance(double x1, double y1, double z1, double x2, double y2, double z2){
	double dx = (x1-x2)*(x1-x2);
	double dy = (y1-y2)*(y1-y2);
	double dz = (z1-z2)*(z1-z2);
	return sqrt(dx+dy+dz);
}

double fx(double x, double y){
	return 10*(y-x);
}
double fy(double x, double y, double z){
	return 28*x-y-x*z;
}
double fz(double x, double y, double z){
	return -8.0/3.0*z+x*y;
}

void integrator(double *x, double *y, double *z, double dt){
	double kx1 = fx(*x, *y);
	double ky1 = fy(*x, *y, *z);
	double kz1 = fz(*x, *y, *z);
	double kx2 = fx(*x + kx1*dt/2.0, *y + ky1*dt/2.0);
	double ky2 = fy(*x + kx1*dt/2.0, *y + ky1*dt/2.0, *z + kz1*dt/2.0);
	double kz2 = fz(*x + kx1*dt/2.0, *y + ky1*dt/2.0, *z + kz1*dt/2.0);
	double kx3 = fx(*x + kx2*dt/2.0, *y + ky2*dt/2.0);
	double ky3 = fy(*x + kx2*dt/2.0, *y + ky2*dt/2.0, *z + kz2*dt/2.0);
	double kz3 = fz(*x + kx2*dt/2.0, *y + ky2*dt/2.0, *z + kz2*dt/2.0);
	double kx4 = fx(*x + kx3*dt, *y + ky3*dt);
	double ky4 = fy(*x + kx3*dt, *y + ky3*dt, *z + kz3*dt);
	double kz4 = fz(*x + kx3*dt, *y + ky3*dt, *z + kz3*dt);
	*x = *x + (kx1+2*kx2+2*kx3+kx4)*dt/6.0;
	*y = *y + (ky1+2*ky2+2*ky3+ky4)*dt/6.0;
	*z = *z + (kz1+2*kz2+2*kz3+kz4)*dt/6.0;
}

int main(){
	
	//parameters
	double x0 = 1.0;
	double y0 = 5.0;
	double z0 = 10.0;
	double t0 = 0.0;
	double trelax = 500.0;
	double tmax = 30.0;
	double dt = 0.01;
	
	double x = x0;
	double y = y0;
	double z = z0;
	for(double t = t0; t < trelax; t = t+dt){
		integrator(&x, &y, &z, dt);
	}
	double x1 = x+0.0001;
	double y1 = y;
	double z1 = z;
	double x2 = x;
	double y2 = y;
	double z2 = z;
	for(double t = t0; t < tmax; t = t+dt){
		integrator(&x1, &y1, &z1, dt);
		integrator(&x2, &y2, &z2, dt);
		cout << t << ", " << log(distance(x1,y1,z1,x2,y2,z2)) << endl;
	}
	
	return 0;
	
}



