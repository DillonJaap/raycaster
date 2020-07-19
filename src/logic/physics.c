#include <SDL.h>
#include "physics.h"
#include "vector.h"
#include "collision.h"

void apply_velocity(Hitbox* hb, Vector2 vel)
{
	move_hitbox(hb, vel.x, vel.y);
}

void limit_velocity(Vector2* vel, double limit)
{
	double magnitude = vector_get_magnitude(*vel);
	if (magnitude > limit)
		*vel = vector_scale(*vel, limit/magnitude);
}

void apply_friction(Vector2* vel, double friction)
{
	*vel = vector_scale(*vel, friction);
}

// bounce a off of b on side "side"
void bounce(Vector2* avel, Vector2* bvel, SIDE side, double multiplier)
{
	if (side == LEFT || side == RIGHT)
	{
		if ((avel->x < 0 && bvel->x > 0 && side == RIGHT) 
				|| (avel->x > 0 && bvel->x < 0 && side == LEFT)
				|| bvel->x == 0)
		{
			avel->x *= -multiplier;
		}
	}

	if (side == BOTTOM || side == TOP)
	{
		if ((avel->y < 0 && bvel->y > 0 && side == BOTTOM)
				|| (avel->y > 0 && bvel->y < 0 && side == TOP)
				|| bvel->y == 0)
		{
			avel->y *= -multiplier;
		}
	}
}
