#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>
#define Pi 3.14159


using namespace std;

double random01(){
	return rand()/double(RAND_MAX);
}

double P(double x){
	return 2.0/Pi*asin(2*x-1);
}

int main(void){
	
	//parameters
	double shift = 1.5;
	double p_shift = 0.3;
	
	//random seed
	srand(time(0));
	
	//random numbers sampling
	for(int i = 0; i < 100000; ++i){
		double r = P(random01());
		if(random01() < p_shift) r = r + shift; 
		cout << r << endl;
	}
	
	return 0;
	
}

