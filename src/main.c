#include <stdio.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "util/util.h"

void spawn_rects(SDL_Rect *rects, int count) {
  for (int i = 0; i < count; i++) {
    int num = 10 * i;
    rects[i].x = num;
    rects[i].y = num;
    rects[i].w = 10;
    rects[i].h = 10;
  }
}

int main(int argc, char **argv) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    print_sdl_error("Could not initialize SDL\n");
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("primitif", 0, 0, 500, 500, 0);
  if (!window) {
    print_sdl_error("Could not initialize SDL window\n");
    return 1;
  }
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
  if (!renderer) {
    print_sdl_error("Could not initialize SDL renderer\n");
    return 1;
  }

  int rects_count = 10;
  SDL_Rect *rects = (SDL_Rect*)malloc(sizeof(SDL_Rect) * rects_count);
  spawn_rects(rects, rects_count);

  SDL_Event event;
  while (1) {
    // events
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) break;

      if (event.type == SDL_KEYDOWN) {
        printf("key pressed: %s\n", SDL_GetKeyName(event.key.keysym.sym));
      }
    }

    // render
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRects(renderer, rects, rects_count);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
  }

  free(rects);

  SDL_Quit();
  return 0;
}
