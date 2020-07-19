#include <stdbool.h>
#include <SDL.h>
#include "ray.h"
#include "vector.h"

Ray init_ray(double x1, double y1, double x2, double y2)
{
	return (Ray){(Vector2){x1, y1}, (Vector2){x2, y2}};
}

bool draw_ray(SDL_Renderer* renderer, Ray r)
{
	SDL_RenderDrawLine(renderer, r.p1.x, r.p1.y, r.p2.x, r.p2.y);
}

bool rays_intersect(Ray r1, Ray r2)
{
	Vector2 sub         = vector_sub(r2.p2, r1.p1);
	double divisor      = vector_cross(r1.p2, r2.p2);

	double v1_dividend  = vector_cross(sub, r1.p2);
	double v1_intersect = v1_dividend/divisor;

	double v2_dividend  = vector_cross(sub, r2.p2);
	double v2_intersect = v2_dividend/divisor;

	// if v2 X v4 = 0, then the two are collinear
	// don't count collinear as intersection
	// TODO maybe change this behavior
	if (divisor == 0 && v2_dividend == 0)
		return false;

	// lines are parallel and non-intersecting
	if (divisor == 0 && v2_dividend != 0)
		return false;

	if (divisor == 0 && 0 <= v1_intersect && v1_intersect <= 1 && 0 <= v2_intersect && v2_intersect <= 1)
		return true;

	// not parallel, but no intersection
	return false;
}
