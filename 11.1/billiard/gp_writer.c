#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

int main(void){

	ofstream fout("gp_animation");
	
	fout << "set terminal gif animate delay 4" << endl;
	fout << "set output \"anim.gif\"" << endl;
	fout << "set xrange [-2:3]" << endl;
	fout << "set yrange [-1:1]" << endl;
	fout << "set size ratio -1" << endl;
	fout << "set nokey" << endl;
	
	for(int i = 0; i < 500; ++i){
		fout << "plot \"saved_files/f_" << i << ".dat\" with points pointtype 7 pointsize 2" << endl;
	}
	
	return 0;
	
}
