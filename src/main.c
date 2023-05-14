#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmshc.h>

#include "frequency.h"
#include "animation.h"


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
	
	if(argc > 2){
		file = fopen(argv[2], "w");
	}

	int ierr;
	gmshInitialize(argc, argv, 0, 0, &ierr);

	gmshOptionSetNumber("General.RotationX", 0, &ierr); 	
	gmshOptionSetNumber("General.Antialiasing", 1, &ierr); 	
	gmshOptionSetNumber("Mesh.SurfaceEdges", 0, &ierr); 	
	gmshOptionSetNumber("Geometry.Points", 0, &ierr); 	
	gmshOptionSetNumber("Geometry.Curves", 0, &ierr); 	
	gmshOptionSetNumber("PostProcessing.AnimationDelay", 0.05, &ierr); 	
	

	int n_vibration_modes = atoi(argv[1]);
	double meshSizeFactor = 0.3;

	double iner_radius = 6e-3;
	double outer_radius = 11e-3;
	double handle_length = 38e-3;

	double correct_l = bin_search_l(iner_radius, outer_radius, handle_length, 0.3, meshSizeFactor, 1e-1);
	printf("correct_l = %lf\n", correct_l);

	double* animation_points;
	int n_nodes;
	
	
	get_k_frequency(file, iner_radius, outer_radius, handle_length, correct_l, meshSizeFactor, n_vibration_modes, true, &animation_points, &n_nodes);
	//get_k_frequency(file,0.0036597497, 0.0221188348, 0.0391091060, 0.0775741736, meshSizeFactor, n_vibration_modes, true, &animation_points, &n_nodes);



	// Compute the harmony now :)
	//double new_l = bin_search_l();



	for(int i = 0; i < n_vibration_modes+1; i++){
		if(i==0) continue;
		generate_animation(0, i, animation_points, n_nodes);
 	}
	
	
	gmshViewCombine("steps", "all", 1, 1, &ierr);
	gmshOptionSetNumber("View.AdaptVisualizationGrid", 1, &ierr); 
	gmshOptionSetNumber("View.LightLines", 0, &ierr); 
	gmshOptionSetNumber("View.SmoothNormals", 1, &ierr); 

	gmshFltkRun(&ierr);
	
	return 0;
}
