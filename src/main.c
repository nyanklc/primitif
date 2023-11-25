
#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#include "util/util.h"


int main(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    print_sdl_error("Could not initialize SDL");
    return 1;
  }

  SDL_Window* win = SDL_CreateWindow("GAME",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     1000, 1000, 0);
  if (!win) {
    print_sdl_error("Could not initialize SDL window");
    return 1;
  }

  SDL_Event event;
  while (1) {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
      break;
  }

  SDL_Quit();
  return 0;
}
