#include "map.h"
#include "objects.h"
#include "walls.h"
#include "collision.h"


Walls* generate_map(int map[])
{
	Walls* walls = init_walls(MAP_LENGTH * MAP_HEIGHT);
	int idx = 0;
	for (int i = 0; i < MAP_LENGTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (map[MAP_LENGTH * i + j] == 1) {
				walls->hbs[idx] = init_hitbox(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE);
				idx++;
			}
		}
	}
	return walls;
}
