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
	Hitbox hb[MAX_WALLS];
} Walls;

Walls* get_walls();
void init_walls(int amount);
bool collides_with_wall(Hitbox hb, Obj** wall);
void draw_walls(SDL_Renderer* renderer);

#endif
