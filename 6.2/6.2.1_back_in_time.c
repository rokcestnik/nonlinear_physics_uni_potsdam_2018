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

double dist(double x, double y){
	return sqrt(x*x+y*y);
}

int main(){
	
	//parameters
	mu = 1.0;
	double delta = 0.01;
	double delta_t = 0.1; //parameter that tells us how far appart in time the points on the limit cycle are
	double t0 = 0.0;
	double tmax = 50.0;
	double dt = 0.01;
	
	//output files
	ofstream fout_xy("xy.dat");
	
	//integration
	double x = 2.2; //arbitrary initial condition
	double y = 3.3; //arbitrary initial condition
	//let the system go to the periodic orbit
	for(double t = t0; t < tmax; t = t+dt){
		integrator(&x, &y, dt);
	}
	//then measure the period
	double period = 0;
	int period_cnt = -1;
	double xh; //previous value of x
	double time_of_crossing;
	for(double t = t0; t < tmax; t = t+dt){
		integrator(&x, &y, dt);
		if(xh < 0 && x > 0){
			if(period_cnt == -1){ //the first time this crosses
				time_of_crossing = t;
				period_cnt = 0;
			}
			else{ //next times it crosses
				period += t-time_of_crossing;
				period_cnt++;
				time_of_crossing = t;
			}
		}
		xh = x;
	}
	period /= period_cnt;
	cout << "period duration: " << period << endl;
	//measure the average x and y
	double x_avg = 0;
	double y_avg = 0;
	int x_cnt = 0;
	int y_cnt = 0;
	for(double t = t0; t < period; t = t+dt){ //average over one period
		integrator(&x, &y, dt);
		x_avg += x;
		y_avg += y;
		x_cnt++;
		y_cnt++;
	}
	x_avg /= x_cnt;
	y_avg /= y_cnt;
	cout << "periodic orbit center: " << x_avg << ", " << y_avg << endl;
	//get points on the period orbit, perturb them and run backwards in time
	int N = period/delta_t; //how many points should we choose
	double x0 = x;
	double y0 = y;
	for(int i = 0; i < N; ++i){
		for(double t = t0; t < delta_t; t = t+dt){
			integrator(&x0, &y0, dt);
		}
		double delta_x = x_avg-x0;
		double delta_y = y_avg-y0;
		//perturb in
		x = x0 + delta*delta_x/dist(delta_x,delta_y);
		y = y0 + delta*delta_y/dist(delta_x,delta_y);
		for(double t = t0; t < tmax; t = t+dt){
			integrator(&x, &y, -dt); //notice we're going back in time
			if(x == x && y == y) fout_xy << x << ", " << y << endl; //check if x or y are not "nan"
		}
		fout_xy << endl;
		//perturb out
		x = x0 - delta*delta_x/dist(delta_x,delta_y);
		y = y0 - delta*delta_y/dist(delta_x,delta_y);
		for(double t = t0; t < tmax; t = t+dt){
			integrator(&x, &y, -dt); //notice we're going back in time
			if(x == x && y == y) fout_xy << x << ", " << y << endl; //check if x or y are not "nan"
		}
		fout_xy << endl;
	}
	
	return 0;
	
}



