#ifndef PRIMITIF_UTIL_FORCE_H
#define PRIMITIF_UTIL_FORCE_H

typedef struct {
  float x;
  float y;
  float value;
} force_t;

void force_normalize(force_t *force);

#endif