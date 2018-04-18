#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>

using namespace std;

double random01(){
	return rand()/double(RAND_MAX);
}

double f(double z, double c){
	return z*z + c;
}

int main(){
	
	srand(time(0));

	double r = random01()*3 - 2;
	
	bool in_set = 1;
	double z = 0;
	for(int i = 0; i < 100; ++i){
		z = f(z, r);
		if(abs(z) > 2){
			in_set = 0;
			break;
		}
	}
	if(in_set) cout << "the number " << r << " is (probably) in the Mandelbrot set" << endl;
	else cout << "the number " << r << " is not in the Mandelbrot set" << endl;
	
	return 0;
	
}


