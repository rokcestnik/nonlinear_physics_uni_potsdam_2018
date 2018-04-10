#include<iostream>

using namespace std;

int main(){
	
	//example 1
	cout << "example 1:" << endl;
	for(int i = 0; i < 10; ++i){
		cout << "i = " << i << endl;
	}
	cout << endl << endl;

	//example 2
	cout << "example 2:" << endl;
	double divisor = 2.0;
	double denominator = 1.0;
	double sum = 0;
	for(int i = 0; i < 100; ++i){
		sum = sum + 1.0/denominator;
		denominator = denominator*divisor;
	}
	cout << "1 + 1/" << divisor << " + 1/" << divisor*divisor << " + 1/" << divisor*divisor*divisor << " + ... = " << sum << endl;
	cout << endl << endl;
	
	//example 3
	cout << "example 3:" << endl;
	for(int i = 0; i < 6; ++i){
		for(int j = 0; j < 23; ++j){
			cout << "*";
		}
		cout << endl;
	}
	cout << endl << endl;
	
	return 0;
	
}
