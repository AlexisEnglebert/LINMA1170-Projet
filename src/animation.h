#pragma once

#include "elasticity.h"

int generate_animation(int i, int j, double* animation_points, int n_nodes);

double lerp(double a, double b, double t);