#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include "vector.h"
#include "collision.h"
#include "objects.h"
#include "walls.h"
#include "player.h"
#include "ball.h"
#include "error.h"
#include "common.h"
#include "ui.h"

#define SCALE 1
#define SCREEN_LENGTH 700
#define SCREEN_HEIGHT 500

bool init(SDL_Window** window, SDL_Renderer** renderer)
{
	printf("start\n");
	check_error(SDL_Init(SDL_INIT_VIDEO), "could not init video");
	printf("vid\n");
	check_error(TTF_Init(), "could not init ttf");
	printf("ttf\n");


	*window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_LENGTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	check_null((void*)window, NULL);

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	check_null((void*)renderer, NULL);

	// disable anisotropic filtering
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
}

void close_stuff(SDL_Window* window, SDL_Renderer* renderer)
{
	//Destroy Window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	TTF_Quit();
	SDL_Quit();
}

bool quit()
{
	SDL_Event e;

	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
			return true;
	}
	return false;
}

void draw_text(SDL_Renderer* renderer, char* text, TTF_Font* font)
{
	SDL_Rect* pos = &(SDL_Rect){0, 0, 40, 80};
	SDL_Color text_color = {0, 0, 0};

	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, text_color);
	check_null((void*)text_surface, "failed to create text_surface");

	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	check_null((void*)text_texture, "failed to create text_texture");

	SDL_RenderCopy(renderer, text_texture, NULL, &(text_surface->clip_rect));
}

int calculacte_fps(int num_frames, int start_time)
{
	return num_frames / ((SDL_GetTicks() - start_time) / 1000.f);
}

int main(int argc, char** argv)
{
	// create window and renderer
	SDL_Window* window     = NULL;
	SDL_Renderer* renderer = NULL;
	init(&window, &renderer);

	TTF_Font* font = TTF_OpenFont("assets/UbuntuMono-Regular.ttf", 18);
	check_null((void*)font, NULL);

	init_players(renderer);
	Player* p1 = get_player1();

	char time_str[100] = "0";

	Uint32 start_time = SDL_GetTicks();
	Uint32 num_frames = 0;
	double avg_fps    = 0;

	while (!quit())
	{
		// handle_inputs
		handle_player_input(p1);
		
		// move objects
		update_player(p1);

		// clear screen
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);

		// draw various game objects and text
		draw_players(renderer);

		// update screen
		SDL_RenderPresent(renderer);

		// finished rendering frame
		num_frames++;

		// calculate FPS 
		if (num_frames % 1 == 0)
		{
			avg_fps = calculacte_fps(num_frames, start_time);
			snprintf(time_str, 100, "FPS: %.2lf ", avg_fps);
		}

		// reset fps count
		if (num_frames > 120)
		{
			num_frames = 0;
			start_time = SDL_GetTicks();
		}
	}

	close_stuff(window, renderer);
	return 0;
}
