#include <SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "common.h"
#include "vector.h"
#include "collision.h"

Hitbox init_hitbox(int x, int y, int w, int h)
{
	return (Hitbox){.top = y, .left = x, .right = x + w, .bottom = y + h};
}

void print_hitbox(Hitbox hb, char* name)
{
	printf("\n");
	printf("Hitbox (%s):\n", name);
	printf("\tleft: %d\n", hb.left);
	printf("\tright: %d\n", hb.right);
	printf("\ttop: %d\n", hb.top);
	printf("\tbottom: %d\n", hb.bottom);
}

SDL_Rect hitbox_to_SDLRect(Hitbox hb)
{
	return (SDL_Rect){
		.x = hb.left,
		.y = hb.top,
	   	.w = hb.right - hb.left,
		.h = hb.bottom - hb.top
	};
}

void move_hitbox(Hitbox* hb, int dx, int dy)
{
	hb->left   += dx;
	hb->right  += dx;
	hb->top    += dy;
	hb->bottom += dy;
}

void set_hitbox(Hitbox* hb, int x, int y)
{
	int length = hb->right  - hb->left;
	int height = hb->bottom - hb->top;

	hb->right  = x + length / 2;
	hb->left   = x - length / 2;
	hb->bottom = y + height / 2;
	hb->top    = y - height / 2;
}

bool collides(Hitbox a, Hitbox b)
{
	if (a.left >= b.right)
		return false;
	if (a.right <= b.left)
		return false;
	if (a.top >= b.bottom)
		return false;
	if (a.bottom <= b.top)
		return false;
	return true;
}

Contact get_contact(Hitbox hb, Hitbox hb_prev, Hitbox hbs[], Hitbox hbs_prev[], size_t len)
{
	SIDE side = NO_SIDE;
	for (int i = 0; i < len; i++)
	{
		side = collides_on_side(hb, hb_prev, hbs[i], hbs_prev[i]);
		if (side != NO_SIDE) 
		{
			printf("side: %d\n", side);
			return (Contact){side, hbs[i]};
		}
	}
	return (Contact){NO_SIDE, {0, 0, 0, 0}};
}

SIDE collides_on_side(Hitbox hba, Hitbox hba_prev, Hitbox hbb, Hitbox hbb_prev)
{
	if (!collides(hba, hbb))
		return NO_SIDE;
	int horizontal_dist = 0;
	int vertical_dist   = 0;
	SIDE horizontal_side = NO_SIDE;
	SIDE vertical_side   = NO_SIDE;

	if (hba_prev.left >= hbb_prev.right)
	{
		horizontal_dist = hbb.right - hba.left;
		horizontal_side = RIGHT;
	}
	else if (hba_prev.right <= hbb_prev.left)
	{
		horizontal_dist =  hbb.left - hba.right;
		horizontal_side = LEFT;
	}

	if (hba_prev.top >= hbb_prev.bottom)
	{
		vertical_dist = hbb.bottom - hba.top;
		vertical_side = BOTTOM;
	}
	else if (hba_prev.bottom <= hbb_prev.top)
	{
		vertical_dist = hbb.top - hba.bottom;
		vertical_side = TOP;
	}

	if (abs(vertical_dist) < abs(horizontal_dist) || vertical_dist == 0)
		return horizontal_side;
	else
		return vertical_side;
}

bool collides_with_edge(Hitbox hb)
{
	return (collides_with_right_edge(hb) 
			|| collides_with_left_edge(hb) 
			|| collides_with_bottom_edge(hb)
			|| collides_with_top_edge(hb));
}

bool collides_with_right_edge(Hitbox hb)
{
	return (hb.right > SCREEN_LENGTH);
}

bool collides_with_left_edge(Hitbox hb)
{
	return (hb.left < 0);
}

bool collides_with_bottom_edge(Hitbox hb)
{
	return (hb.bottom > SCREEN_HEIGHT);
}

bool collides_with_top_edge(Hitbox hb)
{
	return (hb.top < 0);
}

// resolve rectangle and return the side of b that a hit
void resolve_collision(Vector2* apos, Hitbox recta, Hitbox rectb, SIDE side)
{
	// truncate position to avoid overlap
	apos->x = (int)apos->x;
	apos->y = (int)apos->y;
	switch (side)
	{
		case LEFT:   apos->x += rectb.left   - recta.right   - 1; break;
		case RIGHT:  apos->x += rectb.right  - recta.left    + 1; break;
		case TOP:    apos->y += rectb.top    - recta.bottom  - 1; break;
		case BOTTOM: apos->y += rectb.bottom - recta.top     + 1; break;
	}
}

SIDE resolve_edge_collision(Vector2* pos, Hitbox* hb)
{
	int length = hb->right  - hb->left;
	int height = hb->bottom - hb->top;
	if (collides_with_right_edge(*hb))
	{
		pos->x = SCREEN_LENGTH - length / 2;
		return LEFT;
	}
	else if (collides_with_left_edge(*hb))
	{
		pos->x = length / 2;
		return RIGHT;
	}
	if (collides_with_bottom_edge(*hb))
	{
		pos->y = SCREEN_HEIGHT - height / 2;
		return TOP;
	}
	else if (collides_with_top_edge(*hb))
	{
		pos->y = height / 2;
		return BOTTOM;
	}
}

