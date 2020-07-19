#include <SDL.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"

// TODO, make it apply result instead of returning result?
Vector2 vector_add(Vector2 v1, Vector2 v2)
{
	return (Vector2){v1.x + v2.x, v1.y + v2.y};
}

// TODO, make it apply result instead of returning result?
Vector2 vector_sub(Vector2 v1, Vector2 v2)
{
	return (Vector2){v1.x - v2.x, v1.y - v2.y};
}

// TODO, make it apply result instead of returning result?
Vector2 vector_scale(Vector2 v, double scalar)
{
	return (Vector2){v.x * scalar, v.y * scalar};
}

Vector2 vector_add_magnitude(Vector2 v, double amount)
{
	return vector_set_magnitude(v, amount + vector_get_magnitude(v));
}

Vector2 vector_set_magnitude(Vector2 v, double length)
{
	double scale = length / vector_get_magnitude(v);
	return (Vector2){v.x * scale, v.y * scale};
}

double vector_get_magnitude(Vector2 v)
{
	return sqrt(pow(v.x, 2.0) + pow(v.y, 2.0));
}

Vector2 vector_rotate(Vector2 v, double deg)
{
	double rad = deg * (M_PI / 180.0); // degrees to radians
	return (Vector2){
		(cos(rad) * v.x) - (sin(rad) * v.y),
		(sin(rad) * v.x) + (cos(rad) * v.y)
	};
}

Vector2 vector_set_dir(Vector2 v, double deg)
{
	double dir = vector_get_dir(v);
	v = vector_rotate(v,  -dir);
	return vector_rotate(v, deg);
}

double vector_get_dir(Vector2 v)
{
	double dir = atan2(v.y, v.x);
	return dir * (180 / M_PI);
}

double vector_dot(Vector2 v1, Vector2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

// Psuedo cross product (can't do cross product of vectors in 2d space).
// treat vectors as if their Z cordinate is 0
double vector_cross(Vector2 v1, Vector2 v2)
{
	return (v1.x * v2.y) - (v1.y * v2.x);
}


Vector2 get_midpoint(SDL_Rect r)
{
	return (Vector2){(r.x + r.w) / 2, (r.y + r.h) / 2};
}

