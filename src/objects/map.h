#ifndef MAP_H
#define MAP_H

#define TILE_SIZE 10
#define MAP_LENGTH 10
#define MAP_HEIGHT 10

#include "objects.h"
#include "walls.h"
Walls* generate_map(int map[]);

#endif
