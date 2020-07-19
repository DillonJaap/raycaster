#include <SDL2/SDL.h>
#include <stdbool.h>
#include "vector.h"
#include "collision.h"
#include "objects.h"
#include "walls.h"


Walls walls;

Walls* get_walls()
{
	return &walls;
}

void init_walls(int amount)
{
	walls.amount = 0;
	for (int i = 0; i < MAX_WALLS; i++)
		walls.hb[0] = (Hitbox){0,0,0,0};
}

bool collides_with_wall(Hitbox hb, Obj** wall)
{
	for (int i = 0; i < MAX_WALLS; i++)
	{
		if (collides(hb, walls.hb[i]))
		{
			*wall = &walls[i];
			return true;
		}
	}
	*wall = NULL;
	return NULL;
}

void draw_walls(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	for (int i = 0; i < NUM_WALLS; i++)
	{
		rect = hitbox_to_SDLRect(walls[i].hb);
		SDL_RenderCopyEx(renderer, walls[i].texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
	}
}

