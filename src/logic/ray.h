#ifndef RAY_H
#define RAY_H

#include "vector.h"

typedef struct Ray 
{
	Vector2 p1;
	Vector2 p2;
} Ray;

Ray init_ray(double x1, double y1, double x2, double y2);
bool draw_ray(SDL_Renderer* renderer, Ray r);
bool rays_intersect(Ray r1, Ray r2);

#endif
