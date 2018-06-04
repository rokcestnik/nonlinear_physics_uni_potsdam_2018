#include<stdio.h>
#include"8.1.1_isochrones.h"

int main(void){
	
	FILE *f;
	f = fopen("gp_iso","wt");
	fprintf(f, "set size ratio -1\n");
	fprintf(f, "set nokey\n");
	fprintf(f, "plot [-4.5:4.5] [-5:5] \"data/0_in.dat\" with points pt 7 ps 0.5, \\\n");
	for(int i = 1; i < N; ++i){
		fprintf(f, "				   \"data/%d_in.dat\" with points pt 7 ps 0.5, \\\n", i);
	}
	for(int i = 0; i < N; ++i){
		fprintf(f, "				   \"data/%d_out.dat\" with points pt 7 ps 0.5, \\\n", i);
	}
	fprintf(f, "				   \"limit_cycle.dat\" with lines lt rgb \"#FF0000\", \n");
	fprintf(f, "pause -1 \"Hit any key to continue\"\n");
	fclose(f);
	
	return 0;
	
}

