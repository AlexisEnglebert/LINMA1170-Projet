#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmshc.h>

#include "frequency.h"

 #define max(a,b) \
	 ({ __typeof__ (a) _a = (a); \
			 __typeof__ (b) _b = (b); \
		 _a > _b ? _a : _b; })


int main (int argc, char *argv[]) {

	if (argc < 2){
		printf("Usage: \n"
			"./project <k> <out>\n" 
			"---------------------------- \n\n"
			"- k is the number of frequencies to compute. \n "
			"- out is the output file to write the frequencies. \n "
			"\n");
		return -1;
	} 

	FILE * file = stdout;
	
	if(argc < 2){
		file = fopen(argv[2], "w"); // open file to write frequencies
	}

	// Initialize Gmsh and create geometry
	int ierr;
	gmshInitialize(argc, argv, 0, 0, &ierr);

	// Number of vibration modes to find
	int n_vibration_modes = atoi(argv[1]);


	//double freq = get_frequency(6e-3, 11e-3,38e-3, 0.085, 0.3);
	double correct_l = bin_search_l(6e-3, 11e-3,38e-3,0.3, 0.3, 1e-1);
	printf("correct_l = %lf\n", correct_l);
	//double freq = get_frequency(6e-3, 11e-33, 38e-3, 0.085,0.3);
	//printf("LA FAMEUSE FREQUENCE : %.3f \n", freq);

	fclose(file);

	//gmshFltkRun(&ierr);

	

	return 0;
}
