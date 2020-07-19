#include <SDL.h>
#include <math.h>
#include "common.h"
#include "vector.h"
#include "physics.h"
#include "collision.h"
#include "player.h"
#include "objects.h"
#include "walls.h"
#include "ball.h"
#include "ui.h"

#define BALL_MAX_VEL 10
#define NUM_BALLS 1

static Ball balls[NUM_BALLS];

Ball* get_balls()
{
	return balls;
}

void init_balls(SDL_Renderer* renderer)
{
	SDL_Surface* surface = SDL_LoadBMP("./assets/player.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
   	balls[0].hb      = init_hitbox(0, 0, 10, 10);
   	balls[0].prev_hb = init_hitbox(0, 0, 10, 10);

	for (int i = 0; i < NUM_BALLS; i++)
	{
		balls[i].texture = texture;
		ball_serve(&balls[i]);
	}
}

void draw_balls(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	for (int i = 0; i < NUM_BALLS; i++)
	{
		rect = hitbox_to_SDLRect((balls[i]).hb);
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderFillRect(renderer, &rect);
		//SDL_RenderCopyEx(renderer, balls[i].texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
	}

}

void update_ball(Ball* b)
{
	b->prev_hb = b->hb;
	b->pos = vector_add(b->pos, b->vel);
	set_hitbox(&b->hb, b->pos.x, b->pos.y);
	ball_handle_collisions(b);
	limit_velocity(&b->vel, 15.5);
}

void ball_serve(Ball* b)
{
	b->vel = (Vector2){6.0, 0.0};
	b->pos = (Vector2){50.0, 400.0};
}

void ball_handle_collisions(Ball* b)
{
	Player* player;
	Obj* wall;
	Vector2 zero_vel = (Vector2){0.0, 0.0};

	if (collides_with_player(b->hb, &player))
	{
		SIDE side = resolve_collision(&b->pos, &b->hb, b->prev_hb, player->hb, player->prev_hb);
		bounce_off_paddle(b->hb, player->hb, &b->vel, side);
		b->vel = vector_add_magnitude(b->vel, 0.7);
	}

	if (collides_with_wall(b->hb, &wall))
	{
		SIDE side = resolve_collision(&b->pos, &b->hb, b->prev_hb, wall->hb, wall->hb);
		bounce(&b->vel, &zero_vel, side, 1.2);
	}

	if (collides_with_edge(b->hb))
	{
		SIDE side = resolve_edge_collision(&b->pos, &b->hb);
		if (side == LEFT)
		{
			increment_p2_score();
			ball_serve(b);
		}
		else if (side == RIGHT)
		{
			increment_p1_score();
			ball_serve(b);
		}
		else
			bounce(&b->vel, &zero_vel, side, 1.0);
	}
}

void bounce_off_paddle(Hitbox b, Hitbox p, Vector2* vel, SIDE side)
{
	int p_len = p.bottom - p.top;
	int b_len = b.bottom - b.top;

	double dist = (p.bottom + b_len) - b.bottom;

	double ratio = dist / (p_len + b_len);
	double dir = ratio * 70 - 35;

	// if ball hits close enough to center just make it go perfectly horizontal
	if (ratio > 0.40 && ratio <= 0.60)
		dir = 0.0;
	else if (ratio < 0.10)
		dir = 45.0;
	else if (ratio < 0.20)
		dir = 35.0;
	else if (ratio < 0.30)
		dir = 25.0;
	else if (ratio < 0.40)
		dir = 10.0;
	else if (ratio > 0.90)
		dir = -45.0;
	else if (ratio > 0.80)
		dir = -35.0;
	else if (ratio > 0.70)
		dir = -25.0;
	else if (ratio > 0.60)
		dir = -10.0;
	printf("ratio: %lf\n", ratio);
	printf("dir: %lf\n\n", dir);

	switch (side)
	{
		case RIGHT:
			*vel = vector_set_dir(*vel, dir); 
			break;
		case LEFT:
			*vel = vector_set_dir(*vel, 180 - dir);
			break;
		case TOP:
		case BOTTOM:
			vel->y *= -1;
			break;
	}
}

