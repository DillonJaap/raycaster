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

typedef struct Hitbox 
{
	int top;
	int bottom;
	int left;
	int right;
} Hitbox;

typedef struct Contact
{
	SIDE side; // which side did it collide from (NONE if no collision occured)
	Hitbox hb; // hitbox that the player collided with
} Contact;

Hitbox init_hitbox(int x, int y, int w, int h);
void print_hitbox(Hitbox hb, char* name);
SDL_Rect hitbox_to_SDLRect(Hitbox hb);
void move_hitbox(Hitbox* hb, int dx, int dy);
void set_hitbox(Hitbox* hb, int x, int y);
bool collides(Hitbox a, Hitbox b);
Contact get_contact(Hitbox hb, Hitbox hb_prev, Hitbox hbs[], Hitbox hbs_prev[], size_t len);
SIDE collides_on_side(Hitbox recta, Hitbox recta_prev, Hitbox rectb, Hitbox rectb_prev);
bool collides_with_edge(Hitbox hb);
bool collides_with_right_edge(Hitbox hb);
bool collides_with_left_edge(Hitbox hb);
bool collides_with_bottom_edge(Hitbox hb);
bool collides_with_top_edge(Hitbox hb);
void resolve_collision(Vector2* apos, Hitbox recta, Hitbox rectb, SIDE side);
SIDE resolve_edge_collision(Vector2* pos, Hitbox* hb);

#endif
