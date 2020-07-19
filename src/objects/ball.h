#ifndef BALL_H
#define BALL_H

#include <SDL.h>
#include "player.h"
#include "objects.h"
#include "walls.h"
#include "vector.h"
#include "collision.h"


typedef struct Ball
{
	Hitbox hb;
	Hitbox prev_hb;
	Vector2 vel;
	Vector2 pos;
	SDL_Texture* texture;
} Ball;

Ball* get_balls();
void init_balls(SDL_Renderer* renderer);
void draw_balls(SDL_Renderer* renderer);
void update_ball(Ball* b);
void ball_serve(Ball* b);
void ball_handle_collisions(Ball* b);
void bounce_off_paddle(Hitbox b, Hitbox p, Vector2* vel, SIDE side);

#endif
