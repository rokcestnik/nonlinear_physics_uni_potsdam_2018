#include<iostream>
#include<fstream>
#include<cmath>
#define Pi 3.14159

using namespace std;

double coupling(double f1, double f2){
	return -sin(f1-f2)+sin(2*(f1-f2))/2.0;
}

double df(double f1,double f2, double w, double eps){
	return w + eps*coupling(f1,f2);
}

void integrate(double *f1, double *f2, double w1, double w2, double eps21, double eps12, double dt){
	double kf1_1 = df(*f1,*f2,w1,eps21);
	double kf2_1 = df(*f2,*f1,w2,eps12);
	double kf1_2 = df(*f1+kf1_1/2.0*dt,*f2+kf2_1/2.0*dt,w1,eps21);
	double kf2_2 = df(*f2+kf2_1/2.0*dt,*f1+kf1_1/2.0*dt,w2,eps12);
	double kf1_3 = df(*f1+kf1_2/2.0*dt,*f2+kf2_2/2.0*dt,w1,eps21);
	double kf2_3 = df(*f2+kf2_2/2.0*dt,*f1+kf1_2/2.0*dt,w2,eps12);
	double kf1_4 = df(*f1+kf1_3*dt,*f2+kf2_3*dt,w1,eps21);
	double kf2_4 = df(*f2+kf2_3*dt,*f1+kf1_3*dt,w2,eps12);
	*f1 = *f1 + (kf1_1+2*kf1_2+2*kf1_3+kf1_4)/6.0*dt;
	*f2 = *f2 + (kf2_1+2*kf2_2+2*kf2_3+kf2_4)/6.0*dt;
}

int main(void){
	
	//parameters
	double w1 = 3.5;
	double w2 = 1.0;
	double tmax = 500;
	double dt = 0.01;
	double deps = 0.01;
	
	//output files
	ofstream fout_w1("w1.dat");
	ofstream fout_w2("w2.dat");
	ofstream fout_ph("ph.dat");
	
	//initial condition
	double f1 = 0;
	double f2 = 0;
	
	//eps loop
	for(double eps = 0; eps < 2.0; eps += deps){
		if(int(eps/deps)%10 == 0) cout << "eps = " << eps << endl;
		double eps12 = eps;
		double eps21 = eps;
		//integrate to measure frequency and average phase difference
		double f1_0 = f1;
		double f2_0 = f2;
		double avg_phase = 0;
		int phasecnt = 0;
		for(double t = 0; t < tmax; t = t+dt){
			integrate(&f1, &f2, w1, w2, eps21, eps12, dt);
			avg_phase += fmod(fabs(f1-f2),2*Pi);
			phasecnt++;
		}
		double ww1 = (f1-f1_0)/tmax;
		double ww2 = (f2-f2_0)/tmax;
		fout_w1 << eps << ", " << ww1 << endl;
		fout_w2 << eps << ", " << ww2 << endl;
		fout_ph << eps << ", " << avg_phase/phasecnt << endl;
	}
	
	return 0;
	
}

