#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>

void init_ui(SDL_Renderer* renderer);
void init_score(SDL_Renderer* renderer);
void draw_ui(SDL_Renderer* renderer);
void increment_p1_score();
void increment_p2_score();
void update_score();
int check_player_wins();

#endif
