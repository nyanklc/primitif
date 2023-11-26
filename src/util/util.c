#include "util.h"

#include <stdarg.h>
#include <stdio.h>

#include <SDL.h>

void print_sdl_error(const char *msg, ...) {
  va_list ap;
  va_start(ap, msg);
  vprintf(msg, ap);
  printf("%s\n", SDL_GetError());
}

float point_distance(int x1, int y1, int x2, int y2) {
  return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}

