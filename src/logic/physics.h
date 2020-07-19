#ifndef PHYSICS_H
#define PHYSICS_H

#include <SDL.h>
#include "vector.h"
#include "collision.h"

void apply_velocity(Hitbox* hb, Vector2 vel);
void limit_velocity(Vector2* vel, double limit);
void apply_friction(Vector2* vel, double friction);
void bounce(Vector2* avel, Vector2* bvel, SIDE side, double multiplier);

#endif
