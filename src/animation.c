#include "animation.h"

double lerp(double a, double b, double t){
    return (1.0 - t) * a + (t * b);
}

/*
* Generate animation from mode i to mode j.
*/
int generate_animation(int i, int j, double* animation_points, int n_nodes){
    double* start = calloc(sizeof *start, n_nodes);
    double* end = calloc(sizeof *start, n_nodes);
    
    for(int k = 0; k < n_nodes; k++){
        start[k] = animation_points[i*n_nodes+k]; 
        end[k] = animation_points[j*n_nodes+k]; 
    }
    double t = 0;
    double* frame = calloc(sizeof *frame, n_nodes);

    //Normal
    while(t < 1){ //this is our time step;
        for(int k = 0; k < n_nodes; k++){
            frame[k] = lerp(start[k], end[k], t);
        }
        visualize_in_gmsh(frame, n_nodes/2);
        t += 0.05;
    }
   
    //Backward
    t = 0;
    while(t < 1){ //this is our time step;
        for(int k = 0; k < n_nodes; k++){
            frame[k] = lerp(end[k], start[k], t);
        }
        visualize_in_gmsh(frame, n_nodes/2);
        t += 0.05;
    }

    free(start);
    free(end);
    free(frame);
    
    return 0;
}