#pragma once

#include "matrix.h"
#include "elasticity.h"
#include "math.h"
#include "lu.h"
#include "design.h"
#include "eigen.h"

double get_frequency(double r1, double r2, double e, double l, double meshSizeFactor);
