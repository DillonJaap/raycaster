#include "map.h"
#include "objects.h"
#include "walls.h"
#include "collision.h"

#define TILE_SIZE 10
#define MAP_LENGTH 10
#define MAP_HEIGHT 10

int map[MAP_LENGTH * MAP_HEIGHT] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 1, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

Obj* generate_map(int map[])
{
	init_walls(MAP_LENGTH * MAP_HEIGHT);
	Obj* walls = get_walls();
	for (int i = 0; i < MAP_LENGTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (map[MAP_LENGTH * i + j] == 1) {
				walls[i * MAP_LENGTH + j].hb = init_hitbox(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE);
			}
		}
	}
	return walls;
}
