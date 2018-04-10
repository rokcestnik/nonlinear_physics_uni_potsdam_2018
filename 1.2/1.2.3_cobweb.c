#include<iostream>

using namespace std;

int main(){
	
	double r = 2.8; //try also: 2.95, 3.14, 3.5, 3.7
	
	double x = 0.5;
	double xp; //previous x
	for(int n = 0; n < 100; ++n){
		xp = x;
		x = r*x*(1-x);
		cout << xp << " " << xp << endl;
		cout << xp << " " << x << endl;
	}
	
	return 0;
	
}
