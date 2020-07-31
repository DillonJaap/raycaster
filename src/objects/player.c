#include <SDL.h>
#include <math.h>
#include "vector.h"
#include "ray.h"
#include "collision.h"
#include "player.h"
#include "objects.h"
#include "walls.h"
#include "physics.h"
#include "common.h"


#define NUM_PLAYERS 1
#define PLAYER_FRICTION 0.85
static Player players[NUM_PLAYERS];
static Ray rays[1];

Player* get_players()
{
	return players;
}

Player* get_player1()
{
	return &players[0];
}

Player* get_player2()
{
	return &players[1];
}

void init_players(SDL_Renderer* renderer)
{
	SDL_Surface* surface = SDL_LoadBMP("assets/player.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	players[0] = (Player){
		.pos     = (Vector2){100, 100},
		.hb      = init_hitbox(100, 100, 10, 10),
		.prev_hb = init_hitbox(100, 100, 10, 10),
		.contact = {
			.side = NO_SIDE,
			.hb = init_hitbox(0, 0, 0, 0),
		}
	};

	rays[0] = init_ray(0, 0, 0, 0);

	for (int i = 0; i < NUM_PLAYERS; i++)
		players[i].texture = texture;
}

void draw_players(SDL_Renderer* renderer)
{
	SDL_Rect rect;
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		rect = hitbox_to_SDLRect(players[i].hb);
		SDL_SetRenderDrawColor(renderer, 0xda, 0xeb, 0xff, 0xff);
		SDL_RenderFillRect(renderer, &rect);
		draw_ray(renderer, rays[0]);
		//SDL_RenderCopyEx(renderer, players[i].texture, NULL, &rect, 1, NULL, SDL_FLIP_NONE);
	}
}

void update_player(Player* p)
{
	p->prev_hb = p->hb;

	p->dir = modulo(p->dir, 359.0);
	p->pos = vector_add(p->pos, p->vel);
	set_hitbox(&p->hb, p->pos.x, p->pos.y);

	// cast ray in front of player
	rays[0].p1 = p->pos;
	rays[0].p2 = vector_add(p->pos, vector_rotate((Vector2){30, 0}, p->dir));

	player_handle_collisions(p);
	apply_friction(&p->vel, PLAYER_FRICTION);
}

void player_add_velocity(Player* p, double magnitude)
{
	Vector2 dvel = (Vector2){magnitude, 0}; // delta velocity
	dvel = vector_rotate(dvel, p->dir);
	p->vel = vector_add(p->vel, dvel);
}

void handle_player_input(Player* p)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP])
		player_add_velocity(p, 1.0);
	else if (currentKeyStates[SDL_SCANCODE_DOWN])
		player_add_velocity(p, -1.0);
	if (currentKeyStates[SDL_SCANCODE_LEFT])
		p->dir -= 4.0;
	else if (currentKeyStates[SDL_SCANCODE_RIGHT])
		p->dir += 4.0;
}

void player_handle_collisions(Player* p)
{
	Vector2 zero_vel = (Vector2){0.0, 0.0};
	if (p->contact.side != NO_SIDE)
	{
		p->vel.x = 0;
		p->vel.y = 0;
		SIDE side = p->contact.side;
		if (side == LEFT || side == RIGHT)
			p->vel.x = 0;
		else if (side == TOP || side == BOTTOM)
			p->vel.y = 0;
		resolve_collision(&p->pos, p->hb, p->contact.hb, side);
		print_hitbox(p->hb, "Player");
		print_hitbox(p->contact.hb, "Wall");
		printf("x: %lf y: %lf\n", p->pos.x, p->pos.y);
	}
	p->contact.side = NO_SIDE;

	if (collides_with_edge(p->hb))
	{
		SIDE side = resolve_edge_collision(&p->pos, &p->hb);
		if (side == LEFT || side == RIGHT)
			p->vel.x = 0;
		else if (side == TOP || side == BOTTOM)
			p->vel.y = 0;
	}
}

bool collides_with_player(Hitbox hb, Player** player)
{
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		if (collides(hb, players[i].hb))
		{
			*player = &players[i];
			return true;
		}
	}
	*player = NULL;
	return false;
}
