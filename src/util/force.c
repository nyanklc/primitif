#include "force.h"

#include <math.h>

void force_normalize(force_t* force) {
  if (pow(force->x, 2) + pow(force->y, 2) == 1) return;
  float len = sqrt(pow(force->x, 2) + pow(force->y, 2));
  force->x /= len;
  force->y /= len;
}
