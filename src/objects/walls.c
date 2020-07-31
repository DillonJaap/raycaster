#include <SDL2/SDL.h>
#include <stdbool.h>
#include "vector.h"
#include "collision.h"
#include "objects.h"
#include "walls.h"


Walls* init_walls(int amount)
{

	Walls* walls = malloc(sizeof(Walls) + sizeof(Hitbox) * amount);
	walls->amount = amount;
	for (int i = 0; i < amount; i++)
		walls->hbs[i] = (Hitbox){0,0,0,0};
	return walls;
}

void draw_walls(SDL_Renderer* renderer, Walls* walls, int amount)
{
	SDL_Rect rect;
	for (int i = 0; i < amount; i++)
	{
		rect = hitbox_to_SDLRect(walls->hbs[i]);
		SDL_RenderFillRect(renderer, &rect);
	}
}

