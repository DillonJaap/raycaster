#ifndef OBJECTS_H
#define OBJECTS_H

#define NUM_OBJS 1

#include <stdint.h>
#include <SDL.h>
#include <stdbool.h>
#include "collision.h"

typedef struct Obj
{
	Hitbox hb;
	SDL_Texture* texture;
} Obj;

Obj init_objs(SDL_Renderer* renderer);
void draw_obj(SDL_Renderer* renderer, Obj obj);
void draw_objs(SDL_Renderer* renderer, Obj* objs);
Obj* collides_with_obj(Hitbox hb, Obj* objs);


#endif
