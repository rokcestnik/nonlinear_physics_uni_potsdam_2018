#include<stdio.h>
#include"iso.h"

int main(void){
	
	int every = 2;
	
	FILE *f;
	f = fopen("gp","wt");
	fprintf(f, "set size ratio -1\n");
	fprintf(f, "set nokey\n");
	fprintf(f, "plot [-0.6:0.5] [-0.1:0.7] \"data/0_in.dat\" with lines lt rgb \"#999999\", \\\n");
	//fprintf(f, "plot [-2.5:2.5] [-4:4] \"data/0_in.dat\" with points lt rgb \"#999999\", \\\n");
	for(int i = every; i < N; i = i+every){
		fprintf(f, "				   \"data/%d_in.dat\" with lines lt rgb \"#999999\", \\\n", i);
		//fprintf(f, "				   \"data/%d_in.dat\" with points lt rgb \"#999999\", \\\n", i);
	}
	fprintf(f, "				   \"data/0_out.dat\" with lines lt rgb \"#999999\", \\\n");
	//fprintf(f, "				   \"data/0_out.dat\" with points lt rgb \"#999999\", \\\n");
	for(int i = every; i < N; i = i+every){
		fprintf(f, "				   \"data/%d_out.dat\" with lines lt rgb \"#999999\", \\\n", i);
		//fprintf(f, "				   \"data/%d_out.dat\" with points lt rgb \"#999999\", \\\n", i);
	}
	fprintf(f, "				   \"limit_cycle.dat\" with lines lt rgb \"#FF0000\", \n");
	//fprintf(f, "set term pngcairo size 850,500\n");
	//fprintf(f, "set output \"output.png\"\n");
	//fprintf(f, "replot\n");
	//fprintf(f, "set term x11\n");
	fprintf(f, "pause -1 \"Hit any key to continue\"\n");
	fclose(f);
	
	return 0;
	
}

