#include<iostream>

using namespace std;

//function taking the ADDRESS of a variable as parameter and then changing the value at that address
void f(int *x){
	*x = *x+1;
}

int main(){
	
	int x; //declare variable x that will hold a VALUE
	x = 8;
	cout << "x = " << x << endl;	//printout the VALUE of x
	cout << "&x = " << &x << endl << endl;	//printout the ADDRESS of x
	
	int *y; //declare variable y that will hold an ADDRESS
	y = &x; //set an ADDRESS to variable y
	cout << "y = " << y << endl;	//printout the VALUE of y (which is an ADDRESS)
	cout << "*y = " << *y << endl;	//printout the VALUE held at ADDRESS y (which is the value of x)
	cout << "&y = " << &y << endl << endl; 	//printout the ADDRESS of variable y
	
	f(y); //this function changes the value of x
	cout << "after running f(*x), x = " << x << endl;
	
	return 0;
	
}



