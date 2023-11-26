#include "circle.h"

#include <math.h>

circle_t* circle_create(int posx, int posy, float radius) {
  circle_t* circle = (circle_t *)malloc(sizeof(circle_t));
  if (!circle) return NULL;

  circle->x = posx;
  circle->y = posy;
  circle->radius = radius;
  circle->points_count = CIRCLE_DEFAULT_POINT_COUNT;
  if (!circle_construct_points(circle)) {
    free(circle);
    return NULL;
  }
  return circle;
}

void circle_destroy(circle_t* circle) {
  if (!circle) return;
  if (circle->points) free(circle->points);
  if (circle) free(circle);
}

bool circle_construct_points(circle_t* circle) {
  SDL_FPoint *points = (SDL_FPoint *)malloc(sizeof(SDL_FPoint) * circle->points_count);
  if (!points) return false;

  const float angle_inc = 2 * M_PI / circle->points_count;
  float angle = 0;
  for (size_t i = 0; i < circle->points_count; i++) {
    points[i].x = circle->x + circle->radius * cos(angle);
    points[i].y = circle->y - circle->radius * sin(angle);
    angle += angle_inc;
  }

  circle->points = points;
  return true;
}

void circle_render(circle_t* circle, SDL_Renderer* renderer, SDL_Color *color) {
  uint8_t r, g, b, a;
  SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
  SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);

  for (size_t i = 0; i < circle->points_count - 1; i++) {
    SDL_RenderDrawLineF(renderer, circle->points[i].x,
      circle->points[i].y, circle->points[i+1].x,
      circle->points[i+1].y);
  }
  SDL_RenderDrawLineF(renderer,
    circle->points[circle->points_count - 1].x,
    circle->points[circle->points_count - 1].y,
    circle->points[0].x, circle->points[0].y);

  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void circle_move(circle_t* circle, float amountx, float amounty) {
  circle->x += amountx;
  circle->y += amounty;
  for (size_t i = 0; i < circle->points_count; i++) {
    circle->points[i].x += amountx;
    circle->points[i].y += amounty;
  }
}

