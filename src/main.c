#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "electron.h"
#include "util/util.h"

#define WINDOW_W 640
#define WINDOW_H 480

static const int g_rects_count = 10;
static SDL_Rect* g_rects;
SDL_Color g_rects_color = {
  .r = (uint8_t)220,
  .g = (uint8_t)140,
  .b = (uint8_t)90,
  .a = (uint8_t)255
};

static const int g_electrons_count = 20;
static electron_t **g_electrons;
SDL_Color g_electrons_color = {
  .r = (uint8_t)128,
  .g = (uint8_t)128,
  .b = (uint8_t)0,
  .a = (uint8_t)255
};

static SDL_Rect *create_rects(int count) {
  SDL_Rect *rects = (SDL_Rect *)malloc(sizeof(SDL_Rect) * count);
  if (!rects) return NULL;

  for (int i = 0; i < count; i++) {
    int num = 10 * i;
    rects[i].x = num;
    rects[i].y = num;
    rects[i].w = 10;
    rects[i].h = 10;
  }

  return rects;
}

static electron_t **create_electrons(int count) {
  electron_t **electrons = (electron_t**)malloc(sizeof(electron_t*) * count);
  if (!electrons) return NULL;

  for (int i = 0; i < count; i++) {
    int num = 10 * i;
    electrons[i] = electron_create(50 + num, WINDOW_H - 50, 5);

    if (!electrons[i]) {
      for (int j = 0; j <= i; j++)
        free(electrons[j]);
      return NULL;
    }
  }

  return electrons;
}

static void render_rects(SDL_Rect* rects, int count, SDL_Renderer *renderer, SDL_Color *color) {
  uint8_t r, g, b, a;
  SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
  SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);

  SDL_RenderFillRects(renderer, rects, count);

  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

static void render_electrons(electron_t** electrons, int count,
  SDL_Renderer *renderer, SDL_Color *color) {

  for (int i = 0; i < count; i++) {
    electron_render(electrons[i], renderer, color);
  }
}

static void apply_forces_electrons(force_t *forces, electron_t** electrons, int count, float dt) {
  for (int i = 0; i < count; i++) {
    electron_apply_force(electrons[i], &forces[i], dt);
  }
}

static void apply_force_electrons(force_t *force, electron_t** electrons, int count, float dt) {
  for (int i = 0; i < count; i++) {
    electron_apply_force(electrons[i], force, dt);
  }
}

static void update_electrons(electron_t** electrons, int count, float dt) {
  for (int i = 0; i < count; i++) {
    electron_update(electrons[i], dt);
  }
}

static force_t *calculate_mouse_button_forces(SDL_MouseButtonEvent *mbe) {
  force_t* forces;
  forces = (force_t *)malloc(sizeof(force_t) * g_electrons_count);
  if (!forces) return NULL;

  for (int i = 0; i < g_electrons_count; i++) {
    forces[i].value = point_distance(
      mbe->x, mbe->y,
      g_electrons[i]->circle->x,
      g_electrons[i]->circle->y
    );

    forces[i].x = g_electrons[i]->circle->x - mbe->x;
    forces[i].y = g_electrons[i]->circle->y - mbe->y;
    // push
    if (mbe->button == SDL_BUTTON_LEFT) {}
    // pull
    else if (mbe->button == SDL_BUTTON_RIGHT) {
      forces[i].x *= -1;
      forces[i].y *= -1;
    }
    else {
      const char* button_name;
      switch (mbe->button) {
        case SDL_BUTTON_MIDDLE:
          button_name = "Middle";
          break;
        case SDL_BUTTON_X1:
          button_name = "X1";
          break;
        case SDL_BUTTON_X2:
          button_name = "X2";
          break;
        default:
          button_name = "Unknown";
          break;
      }
      printf("unhandled mouse button input: %s\n", button_name);
    }
  }

  return forces;
}

int main(int argc, char **argv) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    print_sdl_error("Could not initialize SDL\n");
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("primitif", 0, 0, WINDOW_W, WINDOW_H, 0);
  if (!window) {
    print_sdl_error("Could not initialize SDL window\n");
    return 1;
  }
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
  if (!renderer) {
    print_sdl_error("Could not initialize SDL renderer\n");
    return 1;
  }

  g_rects = create_rects(g_rects_count);
  if (!g_rects) return 1;
  g_electrons = create_electrons(g_electrons_count);
  if (!g_electrons) return 1;

  const float dt = PRIMITIF_SIM_DT;

  SDL_Event event;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  while (1) {
    // events
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) break;
      if (event.type == SDL_MOUSEBUTTONDOWN) {
        force_t *forces = calculate_mouse_button_forces(&event.button);
        if (forces) {
          apply_forces_electrons(forces, g_electrons, g_electrons_count, dt);
          free(forces);
        }
      }
    }

    update_electrons(g_electrons, g_electrons_count, dt);

    // render
    render_rects(g_rects, g_rects_count, renderer, &g_rects_color);
    render_electrons(g_electrons, g_electrons_count, renderer, &g_electrons_color);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
  }

  free(g_rects);
  free(g_electrons);
  SDL_Quit();
  return 0;
}
