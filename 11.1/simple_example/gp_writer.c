#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

int main(void){

	ofstream fout("gp_animation");
	
	fout << "set terminal gif animate delay 5" << endl;
	fout << "set output \"anim.gif\"" << endl;
	fout << "set xrange [-3.14159:3.14159]" << endl;
	fout << "set yrange [-2:2]" << endl;
	
	for(double c = 0; c < 2*3.14159; c = c+0.1){
		fout << "plot " << sin(c) << "*sin(x)" << endl;
	}
	
	return 0;
	
}
