#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

double beta;
double gama;
double n;

double dx(double x, double xtau){
	return beta*xtau/(1+pow(xtau,n)) - gama*x;
}

double integrator(double x, double xtau, double dt){
	double k1 = dx(x,xtau);
	double k2 = dx(x+k1/2*dt,xtau);
	double k3 = dx(x+k2/2*dt,xtau);
	double k4 = dx(x+k3*dt,xtau);
	return x + (k1+2*k2+2*k3+k4)/6*dt;
}

int main(void){
	
	//parameters
	beta = 2;
	gama = 1;
	double tau = 2;
	double dt = 0.05;
	double tmax = 800;
	double twarmup = 200;
	
	//history
	int N = tau/dt; //how much history must be kept
	double x_buf[N]; //the historical values buffer
	
	//output files
	ofstream fout_bif("bif.dat");
		
	for(n = 5; n < 11; n += 0.01){
		//initial condition
		for(int i = 0; i < N; ++i) x_buf[i] = 0.5;
		int x_index = 0;
		//warm up integration
		for(double t = 0; t < twarmup; t = t+dt){
			x_buf[(x_index+1)%N] = integrator(x_buf[x_index],x_buf[(x_index+1)%N],dt);
			//index increase
			x_index = (x_index+1)%N;
		}
		//integration
		for(double t = 0; t < tmax; t = t+dt){
			x_buf[(x_index+1)%N] = integrator(x_buf[x_index],x_buf[(x_index+1)%N],dt);
			//index increase
			x_index = (x_index+1)%N;
			//file print
			double x1 = x_buf[(x_index+1)%N]; //x(t-tau)
			double x2 = x_buf[(x_index+2)%N]; //x(t-tau+dt)
			double x3 = x_buf[(x_index+3)%N]; //x(t-tau+2*dt)
			if(x2 > x1 && x2 > x3){
				fout_bif << n << ", " << x2 << endl;
			}
		}
	}
	
	return 0;
	
}

