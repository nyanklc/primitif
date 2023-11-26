#ifndef PRIMITIF_UTIL_CIRCLE_H
#define PRIMITIF_UTIL_CIRCLE_H

#include <SDL.h>

#include <stdbool.h>

#include "../globals.h"

typedef struct {
  float x;
  float y;
  float radius;
  SDL_FPoint *points;
  size_t points_count;
} circle_t;

circle_t* circle_create(int posx, int posy, float radius);
void circle_destroy(circle_t *circle);
bool circle_construct_points(circle_t* circle);
void circle_render(circle_t* circle, SDL_Renderer* renderer, SDL_Color* color);
void circle_move(circle_t* circle, float amountx, float amounty);

#endif