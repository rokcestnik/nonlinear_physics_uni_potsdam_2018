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
	n = 9.65;
	double tau = 2;
	double dt = 0.05;
	double tmax = 100;
	
	//history
	int N = tau/dt; //how much history must be kept
	double x_buf[N]; //the historical values buffer
	
	//initial condition
	for(int i = 0; i < N; ++i) x_buf[i] = 0.5;
	int x_index = 0;
	
	//output files
	ofstream fout_x("x.dat");
	ofstream fout_xxtau("x_xtau.dat");
	
	//integration
	for(double t = 0; t < tmax; t = t+dt){
		x_buf[(x_index+1)%N] = integrator(x_buf[x_index],x_buf[(x_index+1)%N],dt);
		//index increase
		x_index = (x_index+1)%N;
		//file print
		double x = x_buf[x_index]; //x(t)
		fout_x << t << ", " << x << endl;
		double xtau = x_buf[(x_index+1)%N]; //x(t-tau)
		double xtau2 = x_buf[int(x_index+ceil(N/2.0))%N]; //x(t-tau/2)
		fout_xxtau << x << ", " << xtau2 << ", " << xtau << endl;
	}
	
	return 0;
	
}

