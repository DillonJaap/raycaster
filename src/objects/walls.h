#ifndef WALLS_H
#define WALLS_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "objects.h"
#include "vector.h"
#include "collision.h"

#define MAX_WALLS 100

typedef struct Walls
{
	int amount;
	Hitbox hbs[];
} Walls;

Walls* init_walls(int amount);
void draw_walls(SDL_Renderer* renderer, Walls* walls, int amount);

#endif
