#include <SDL2/SDL.h>
#include <stdbool.h>
#include "objects.h"
#include "common.h"


void draw_obj(SDL_Renderer* renderer, Obj obj)
{
	SDL_Rect rect = hitbox_to_SDLRect(obj.hb);
	SDL_RenderCopyEx(renderer, obj.texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
}

void draw_objs(SDL_Renderer* renderer, Obj* objs)
{
	for (int i = 0; i < 1; i++)
		draw_obj(renderer, objs[i]);
}


Obj* collides_with_obj(Hitbox hb, Obj* objs)
{
	for (int i = 0; i < NUM_OBJS; i++)
	{
		if (collides(hb, objs[i].hb))
			return &objs[i];
	}
	return NULL;
}
