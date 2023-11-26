#ifndef PRIMITIF_ELECTRON_H
#define PRIMITIF_ELECTRON_H

#include <SDL.h>

#include "util/circle.h"

typedef struct {
  circle_t *circle;
  float charge;
} electron_t;

electron_t* electron_create(int posx, int posy, float radius);
void electron_destroy(electron_t * electron);
void electron_render(electron_t * electron, SDL_Renderer * renderer, SDL_Color * color);
void electron_move(electron_t * electron, int amountx, int amounty);
#endif