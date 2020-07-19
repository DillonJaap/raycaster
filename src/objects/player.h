#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "objects.h"
#include "vector.h"
#include "collision.h"

typedef struct Player
{
	Vector2 pos;
	Vector2 vel;
	double dir;

	Hitbox hb;
	Hitbox prev_hb;

	SDL_Texture* texture;
} Player;

Player* get_players();
Player* get_player1();
Player* get_player2();
void init_players(SDL_Renderer* renderer);
void draw_players(SDL_Renderer* renderer);
void update_player(Player* p);
void handle_player_input(Player* p);
void player_handle_collisions(Player* p);
bool collides_with_player(Hitbox hb, Player** player);

#endif
