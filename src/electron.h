#ifndef PRIMITIF_ELECTRON_H
#define PRIMITIF_ELECTRON_H

#include <SDL.h>

#include "util/circle.h"
#include "util/force.h"
#include "util/velocity.h"

typedef struct {
  circle_t *circle;
  float charge;
  float mass;
  velocity_t vel;
} electron_t;

electron_t* electron_create(int posx, int posy, float radius);
void electron_destroy(electron_t * electron);
void electron_render(electron_t * electron, SDL_Renderer * renderer, SDL_Color * color);
void electron_move(electron_t * electron, float amountx, float amounty);
void electron_apply_force(electron_t *electron, force_t *force, float duration);
void electron_update(electron_t* electron, float dt);
#endif