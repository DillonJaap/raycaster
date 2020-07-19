#ifndef VECTOR_H
#define VECTOR_H

#include <SDL.h>
#include <stdbool.h>

typedef struct Vector2 
{
	double x;
	double y;
} Vector2;

Vector2 vector_add(Vector2 v1, Vector2 v2);
Vector2 vector_sub(Vector2 v1, Vector2 v2);
Vector2 vector_scale(Vector2 v, double scalar);
Vector2 vector_rotate(Vector2 v, double deg);
Vector2 vector_set_dir(Vector2 v, double deg);
Vector2 vector_add_magnitude(Vector2 v, double amount);
Vector2 vector_set_magnitude(Vector2 v, double length);
double  vector_get_magnitude(Vector2 v);
double  vector_get_dir(Vector2 v);
double  vector_dot(Vector2 v1, Vector2 v2);
double  vector_cross(Vector2 v1, Vector2 v2);
Vector2 get_midpoint(SDL_Rect r);
bool    lines_intersect(Vector2 v1_beg, Vector2 v1_end, Vector2 v2_beg, Vector2 v2_end);

#endif
