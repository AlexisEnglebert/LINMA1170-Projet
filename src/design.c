
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmshc.h>

void designMultipleTuningFork(double handle_length, double base_prongs_length, double space_between_base_branch,
                             double space_between_second_layer, double second_prongs_length, double meshSizeFactor,
                            char * filename)
{
  double iner_radius = 8e-3;
	double outer_radius = 11e-3;


  

  int ierr;

  double h = outer_radius - iner_radius;
  
  double h2 = h/2.0; // for upper fork

  double meshSize = h*meshSizeFactor;


  gmshClear(&ierr);
  double x = 0; 
  double y = 0; 
  double z = 0;
  gmshModelOccAddPoint(x,y,z,meshSize,1,&ierr);
  x += h;
  gmshModelOccAddPoint(x,y,z,meshSize,2,&ierr);
  y += handle_length;
  gmshModelOccAddPoint(x,y,z,meshSize,3,&ierr);
  x += iner_radius;
  gmshModelOccAddPoint(x,y,z,meshSize,4,&ierr);
  y += iner_radius;
  gmshModelOccAddPoint(x,y,z,meshSize,5,&ierr);
  y += base_prongs_length;
  gmshModelOccAddPoint(x,y,z,meshSize,6,&ierr);

  //start of second tunning fork on top right
  x += iner_radius/2.0;
  gmshModelOccAddPoint(x,y,z,meshSize,7,&ierr);
  y += iner_radius/2.0;
  gmshModelOccAddPoint(x,y,z,meshSize,8,&ierr);
  y += second_prongs_length;
  gmshModelOccAddPoint(x,y,z,meshSize,9,&ierr);
  x -= h2;
  gmshModelOccAddPoint(x,y,z,meshSize,10,&ierr);
  y -= second_prongs_length;
  gmshModelOccAddPoint(x,y,z,meshSize,11,&ierr);
  x -= space_between_second_layer;
  x -= iner_radius;
  gmshModelOccAddPoint(x,y,z,meshSize,12,&ierr);
  y += second_prongs_length;
  gmshModelOccAddPoint(x,y,z,meshSize,13,&ierr);
  x -= h2;
  gmshModelOccAddPoint(x,y,z,meshSize,14,&ierr);
  y -= second_prongs_length;
  gmshModelOccAddPoint(x,y,z,meshSize,15,&ierr);
  y -= iner_radius/2.0;
  gmshModelOccAddPoint(x,y,z,meshSize,16,&ierr);
  x += iner_radius/2.0;
  gmshModelOccAddPoint(x,y,z,meshSize,17,&ierr);
  // finished second tuning fork on top right

  y -= base_prongs_length;
  gmshModelOccAddPoint(x,y,z,meshSize,18,&ierr);
  x-= space_between_base_branch;
  gmshModelOccAddPoint(x,y,z,meshSize,19,&ierr);
  y += base_prongs_length;
  gmshModelOccAddPoint(x,y,z,meshSize,20,&ierr);
  //start of the second tuning fork on top left
  x += iner_radius/2.0;
  gmshModelOccAddPoint(x,y,z,meshSize,21,&ierr);
  y += iner_radius/2.0;
  gmshModelOccAddPoint(x,y,z,meshSize,22,&ierr);
  y += second_prongs_length;
  gmshModelOccAddPoint(x,y,z,meshSize,23,&ierr);
  x -= h2;
  gmshModelOccAddPoint(x,y,z,meshSize,24,&ierr);
  y -= second_prongs_length;
  gmshModelOccAddPoint(x,y,z,meshSize,25,&ierr);
  x -= space_between_second_layer;
  x -= iner_radius;
  gmshModelOccAddPoint(x,y,z,meshSize,26,&ierr);
  y += second_prongs_length;
  gmshModelOccAddPoint(x,y,z,meshSize,27,&ierr);
  x -= h2;
  gmshModelOccAddPoint(x,y,z,meshSize,28,&ierr);
  y -= second_prongs_length;
  gmshModelOccAddPoint(x,y,z,meshSize,29,&ierr);
  y -= iner_radius/2.0;
  gmshModelOccAddPoint(x,y,z,meshSize,30,&ierr);
  x += iner_radius/2.0;
  gmshModelOccAddPoint(x,y,z,meshSize,31,&ierr);
  // finished second tuning fork on top left
  y -= base_prongs_length;
  gmshModelOccAddPoint(x,y,z,meshSize,32,&ierr);
  y -= iner_radius;
  gmshModelOccAddPoint(x,y,z,meshSize,33,&ierr);
  x += iner_radius;
  gmshModelOccAddPoint(x,y,z,meshSize,34,&ierr);
  y -= handle_length;
  gmshModelOccAddPoint(x,y,z,meshSize,35,&ierr);


  gmshModelOccAddLine(1,2,1,&ierr);
  gmshModelOccAddLine(2,3,2,&ierr);
  gmshModelOccAddLine(3,4,3,&ierr);
  gmshModelOccAddLine(4,5,4,&ierr);
  gmshModelOccAddLine(5,6,5,&ierr);
  gmshModelOccAddLine(6,7,6,&ierr);
  gmshModelOccAddLine(7,8,7,&ierr);
  gmshModelOccAddLine(8,9,8,&ierr);
  gmshModelOccAddLine(9,10,9,&ierr);
  gmshModelOccAddLine(10,11,10,&ierr);
  gmshModelOccAddLine(11,12,11,&ierr);
  gmshModelOccAddLine(12,13,12,&ierr);
  gmshModelOccAddLine(13,14,13,&ierr);
  gmshModelOccAddLine(14,15,14,&ierr);
  gmshModelOccAddLine(15,16,15,&ierr);
  gmshModelOccAddLine(16,17,16,&ierr);
  gmshModelOccAddLine(17,18,17,&ierr);
  gmshModelOccAddLine(18,19,18,&ierr);
  gmshModelOccAddLine(19,20,19,&ierr);
  gmshModelOccAddLine(20,21,20,&ierr);
  gmshModelOccAddLine(21,22,21,&ierr);
  gmshModelOccAddLine(22,23,22,&ierr);
  gmshModelOccAddLine(23,24,23,&ierr);
  gmshModelOccAddLine(24,25,24,&ierr);
  gmshModelOccAddLine(25,26,25,&ierr);
  gmshModelOccAddLine(26,27,26,&ierr);
  gmshModelOccAddLine(27,28,27,&ierr);
  gmshModelOccAddLine(28,29,28,&ierr);
  gmshModelOccAddLine(29,30,29,&ierr);
  gmshModelOccAddLine(30,31,30,&ierr);
  gmshModelOccAddLine(31,32,31,&ierr);
  gmshModelOccAddLine(32,33,32,&ierr);
  gmshModelOccAddLine(33,34,33,&ierr);
  gmshModelOccAddLine(34,35,34,&ierr);
  gmshModelOccAddLine(35,1,35,&ierr);


  int curveTags[35] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};
  gmshModelOccAddWire(curveTags, 35, 1, 1, &ierr);

  int wireTags[1] = {1};
  gmshModelOccAddPlaneSurface(wireTags, 1, 100, &ierr);


  gmshModelOccSynchronize(&ierr);

  int surfaceTags[1] = {100};
  gmshModelAddPhysicalGroup(2, surfaceTags, 1, -1, "bulk", &ierr);

  int clampedCurveTags[4] = {35, 2, 1, 34};
  gmshModelAddPhysicalGroup(1, clampedCurveTags, 4, -1, "clamped", &ierr);


  gmshModelMeshGenerate(2, &ierr);

  if(filename != NULL){
    gmshWrite(filename, &ierr);
  }
}


void designTuningFork(double r1, double r2, double e, double l, double meshSizeFactor, char * filename) {
  /**
   * r1 = inner radius (half-distance between prongs)
   * r2 = outer radius (half-width of fork)
   * e  = length of handle
   * l  = length of prongs
   * meshSizeFactor = meshSize / width of prongs
   * if `filename` is not NULL, save to file
  */
  
  int ierr;

  gmshClear(&ierr);

  double h = r2 - r1; // width of prongs
  double meshSize = h * meshSizeFactor;

  // Add points
  double x = 0;
  double y = 0;
  double z = 0;
  gmshModelOccAddPoint(x,y,z,meshSize,1,&ierr);
  x += h;
  gmshModelOccAddPoint(x,y,z,meshSize,2,&ierr);
  y += e;
  gmshModelOccAddPoint(x,y,z,meshSize,3,&ierr);
  x += r2;
  y += r2;
  gmshModelOccAddPoint(x,y,z,meshSize,4,&ierr);
  y += l;
  gmshModelOccAddPoint(x,y,z,meshSize,5,&ierr);
  x -= h;
  gmshModelOccAddPoint(x,y,z,meshSize,6,&ierr);
  y -= l;
  gmshModelOccAddPoint(x,y,z,meshSize,7,&ierr);
  x -= r1;
  y -= r1;
  gmshModelOccAddPoint(x,y,z,meshSize,8,&ierr);
  x -= h;
  gmshModelOccAddPoint(x,y,z,meshSize,9,&ierr);
  x -= r1;
  y += r1;
  gmshModelOccAddPoint(x,y,z,meshSize,10,&ierr);
  y += l;
  gmshModelOccAddPoint(x,y,z,meshSize,11,&ierr);
  x -= h;
  gmshModelOccAddPoint(x,y,z,meshSize,12,&ierr);
  y -= l;
  gmshModelOccAddPoint(x,y,z,meshSize,13,&ierr);
  x += r2;
  y -= r2;
  gmshModelOccAddPoint(x,y,z,meshSize,14,&ierr);
  y += (h+r1);
  gmshModelOccAddPoint(x,y,z,meshSize,15,&ierr);
  x += h;
  gmshModelOccAddPoint(x,y,z,meshSize,16,&ierr);
  
  // Add curves
  gmshModelOccAddLine(1,2,1,&ierr);
  gmshModelOccAddLine(2,3,2,&ierr);
  gmshModelOccAddCircleArc(3,16,4,3,&ierr);
  gmshModelOccAddLine(4,5,4,&ierr);
  gmshModelOccAddLine(5,6,5,&ierr);
  gmshModelOccAddLine(6,7,6,&ierr);
  gmshModelOccAddCircleArc(7,16,8,7,&ierr);
  gmshModelOccAddLine(8,9,8,&ierr);
  gmshModelOccAddCircleArc(9,15,10,9,&ierr);
  gmshModelOccAddLine(10,11,10,&ierr);
  gmshModelOccAddLine(11,12,11,&ierr);
  gmshModelOccAddLine(12,13,12,&ierr);
  gmshModelOccAddCircleArc(13,15,14,13,&ierr);
  gmshModelOccAddLine(14,1,14,&ierr);

  // Add wire (closed curve)
  int curveTags[14] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
  gmshModelOccAddWire(curveTags, 14, 1, 1, &ierr);

  // Add surface
  int wireTags[1] = {1};
  gmshModelOccAddPlaneSurface(wireTags, 1, 100, &ierr);

  // Sync
  gmshModelOccSynchronize(&ierr);

  // Create physical group for surface
  int surfaceTags[1] = {100};
  gmshModelAddPhysicalGroup(2, surfaceTags, 1, -1, "bulk", &ierr);

  // Create physical group for clamped curves
  int clampedCurveTags[3] = {1, 2, 14};
  gmshModelAddPhysicalGroup(1, clampedCurveTags, 3, -1, "clamped", &ierr);

  gmshModelMeshGenerate(2, &ierr);

  if(filename != NULL){
    gmshWrite(filename, &ierr);
  }
}
