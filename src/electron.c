#include "electron.h"

electron_t* electron_create(int posx, int posy, float radius) {
	electron_t* electron = (electron_t *)malloc(sizeof(electron_t));
	if (!electron) return NULL;

	electron->circle = circle_create(posx, posy, radius);
	electron->charge = ELECTRON_DEFAULT_CHARGE;
	electron->mass = ELECTRON_DEFAULT_MASS;
	electron->vel.x = 0;
	electron->vel.y = 0;
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

void electron_move(electron_t* electron, float amountx, float amounty) {
	circle_move(electron->circle, amountx, amounty);
}

void electron_apply_force(electron_t* electron, force_t* force, float duration) {
	force_normalize(force);
	electron->vel.x += force->x * force->value * duration / electron->mass;
	electron->vel.y += force->y * force->value * duration / electron->mass;
}

void electron_update(electron_t *electron, float dt) {
	if (electron->vel.x == 0 && electron->vel.y == 0) return;
	electron_move(electron, electron->vel.x * dt, electron->vel.y * dt);
}

