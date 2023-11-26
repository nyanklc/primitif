#include "electron.h"

electron_t* electron_create(int posx, int posy, float radius) {
	electron_t* electron = (electron_t *)malloc(sizeof(electron_t));
	if (!electron) return NULL;

	electron->circle = circle_create(posx, posy, radius);
	electron->charge = ELECTRON_DEFAULT_CHARGE;
	return electron;
}

void electron_destroy(electron_t* electron) {
	if (!electron) return;
	if (electron->circle) circle_destroy(electron->circle);
	if (electron) free(electron);
}

void electron_render(electron_t* electron, SDL_Renderer* renderer, SDL_Color *color) {
	circle_render(electron->circle, renderer, color);
}

void electron_move(electron_t* electron, int amountx, int amounty) {
	circle_move(electron->circle, amountx, amounty);
}

