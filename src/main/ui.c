#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include "ui.h"

static int p1_score = 0;
static int p2_score = 0;


struct
{
	// TODO cleaner way to use the renderer without just putting a pointer to it in the struct
	SDL_Renderer* renderer;
	SDL_Texture* logo;
	TTF_Font* font;
	struct
	{
		SDL_Texture* p1_texture;
		SDL_Texture* p2_texture;
		SDL_Texture* wins_texture;
		int p1_score;
		int p2_score;
		char p1_text[4];
		char p2_text[4];
		char wins_text[32];
		SDL_Rect p1_pos;
		SDL_Rect p2_pos;
		SDL_Rect wins_pos;
	} score;
} ui;


void init_ui(SDL_Renderer* renderer)
{
	SDL_Surface* surface = SDL_LoadBMP("assets/logo.bmp");
	ui.renderer = renderer;
	ui.logo  = SDL_CreateTextureFromSurface(renderer, surface);
	ui.font = TTF_OpenFont("assets/UbuntuMono-Regular.ttf", 22);

	init_score(renderer);
}

void init_score(SDL_Renderer* renderer)
{
	SDL_Surface* text_surface;
	SDL_Color text_color = {255, 255, 255};

	ui.score.p1_score = 0;
	ui.score.p2_score = 0;

	ui.score.p1_pos   = (SDL_Rect){500, 0, 50, 75};
	ui.score.p2_pos   = (SDL_Rect){700 - 500 - 50, 0, 50, 75};
	ui.score.wins_pos = (SDL_Rect){700/2 - 300, 100, 300, 75};

	sprintf(ui.score.p1_text, "%d", ui.score.p1_score);
	sprintf(ui.score.p2_text, "%d", ui.score.p2_score);
	sprintf(ui.score.wins_text, "");

	text_surface = TTF_RenderText_Solid(ui.font, ui.score.p1_text, text_color);
	ui.score.p1_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

	text_surface = TTF_RenderText_Solid(ui.font, ui.score.p2_text, text_color);
	ui.score.p2_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

	SDL_FreeSurface(text_surface);
}

void draw_ui(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderCopyEx(renderer, ui.logo, NULL, &(SDL_Rect){700/2 - 114/2, 10, 114, 34}, 1, NULL, SDL_FLIP_NONE);

	SDL_RenderCopy(renderer, ui.score.p1_texture, NULL, &ui.score.p1_pos);
	SDL_RenderCopy(renderer, ui.score.p2_texture, NULL, &ui.score.p2_pos);
	SDL_RenderCopy(renderer, ui.score.wins_texture, NULL, &ui.score.wins_pos);

}

void increment_p1_score()
{
	ui.score.p1_score++;
	update_score();
}

void increment_p2_score()
{
	ui.score.p2_score++;
	update_score();
}

void update_score()
{
	SDL_Surface* text_surface;
	SDL_Color text_color = {255, 255, 255};

	SDL_DestroyTexture(ui.score.p1_texture);
	SDL_DestroyTexture(ui.score.p2_texture);
	SDL_DestroyTexture(ui.score.wins_texture);

	sprintf(ui.score.p1_text, "%d", ui.score.p1_score);
	sprintf(ui.score.p2_text, "%d", ui.score.p2_score);

	text_surface = TTF_RenderText_Solid(ui.font, ui.score.p1_text, text_color);
	ui.score.p1_texture = SDL_CreateTextureFromSurface(ui.renderer, text_surface);

	text_surface = TTF_RenderText_Solid(ui.font, ui.score.p2_text, text_color);
	ui.score.p2_texture = SDL_CreateTextureFromSurface(ui.renderer, text_surface);

	int winner = check_player_wins();
	if (winner)
	{
		sprintf(ui.score.wins_text, "Player %d, Wins!", winner);
		text_surface = TTF_RenderText_Solid(ui.font, ui.score.wins_text, text_color);
		ui.score.wins_texture = SDL_CreateTextureFromSurface(ui.renderer, text_surface);
	}

	SDL_FreeSurface(text_surface);
}

int check_player_wins()
{
	if (ui.score.p1_score > 9)
		return 1;
	if (ui.score.p2_score > 9)
		return 2;
	return 0;
}

