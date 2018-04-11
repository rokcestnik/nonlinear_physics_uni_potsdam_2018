#include<iostream>

int main(){
	
	//integers
	int a = 1;
	int b = 2;
	int c = a+b;	//c = 3
	
	int d;
	d = 3;			//d = 3
	d = d+d;		//d = 6
	d = d*d;		//d = 36
	
	int e;
	e = d/b;		//e = 18
	e = a/b;		//e = 0  (not 0.5, because a, b, e are integers)
	
	//floating point numbers
	double f, g, h;
	f = 1.0;
	g = 2.0;
	h = f/g;		//h = 0.5
	h = a/b;		//h = 0  (because a and b are integers)
	
	return 0;
	
}

