#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>
#include <stdbool.h>
#include "vector.h"

typedef enum SIDE {
	NO_SIDE = 0,
	LEFT = 1,
	RIGHT = 2,
	TOP = 3,
	BOTTOM = 4
} SIDE;

typedef struct Hitbox {
	int top;
	int bottom;
	int left;
	int right;
} Hitbox;

struct contact
{
	// which side did it collide from (NONE if no collision occured)
	SIDE side; 
	// hitbox that the player collided with
	Hitbox hb; 
} contact;

Hitbox init_hitbox(int x, int y, int w, int h);
SDL_Rect hitbox_to_SDLRect(Hitbox hb);

Hitbox init_hitbox(int x, int y, int w, int h);
void print_hitbox(Hitbox hb, char* name);
SDL_Rect hitbox_to_SDLRect(Hitbox hb);
void move_hitbox(Hitbox* hb, int dx, int dy);
void set_hitbox(Hitbox* hb, int x, int y);
bool collides(Hitbox a, Hitbox b);
bool collides_with_edge(Hitbox hb);
bool collides_with_right_edge(Hitbox hb);
bool collides_with_left_edge(Hitbox hb);
bool collides_with_bottom_edge(Hitbox hb);
bool collides_with_top_edge(Hitbox hb);
SIDE resolve_collision(Vector2* apos, Hitbox* recta, Hitbox recta_prev, Hitbox rectb, Hitbox rectb_prev);
SIDE resolve_edge_collision(Vector2* pos, Hitbox* hb);

#endif
