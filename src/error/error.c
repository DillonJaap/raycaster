#include <stdint.h>
#include <SDL.h>
#include "error.h"

// check if SDL function returned an error (e.g. returns -1)
void check_error(int val, char* msg)
{
	if (val < 0)
	{
		print_error(msg);
		exit(1);
	}
}

// check if variable is null after assignemnt from SDL function
void check_null(void* val, char* msg)
{
	if (val == NULL)
	{
		print_error(msg);
		exit(1);
	}
}

void print_error(char* msg)
{
	const char* sdl_error = SDL_GetError();
	if (msg == NULL)
		fprintf(stderr, "%s\n", sdl_error);
	else if (sdl_error[0] == '\0')
		fprintf(stderr, "%s\n", msg);
	else
		fprintf(stderr, "%s: %s\n", msg, sdl_error);
}
