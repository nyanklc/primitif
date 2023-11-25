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

