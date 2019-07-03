#include "wolf3d.h"

void	pixel_put(t_wolf *wolf, int x, int y, int c)
{
	int				i;
	unsigned int	p;

	i = -1;
	p = y * (LINESIZE) + x * (BPP / 8);
	while (++i < (BPP / 8))
	{
		ADDR[p + i] = c;
		c >>= 8;
	}
}

void	radar_dot(t_wolf *wolf, int x, int y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
			pixel_put(wolf, x + i, y + j, color);
	}
}

void	display_radar(t_wolf *wolf)
{
	int x;
	int y;

	x = -1;
	while (++x < LENGTH)
	{
		y = -1;
		while (++y < LNUMBER)
		{
			if (KARTA[y][x] == '1')
				radar_dot(wolf, x * 10 + 5, y * 10 + 5, RED);
			else
				radar_dot(wolf, x * 10 + 5, y * 10 + 5, WHITE);
			if (((int)XPOS == y && (int)YPOS == x))
				radar_dot(wolf, x * 10 + 5, y * 10 + 5, BLACK);
		}
	}
}

int		fill_wall(t_wolf *wolf)
{
	int		c;

	if (SIDE == 0 && XDIRCAM >= 0)
		c = SOUTH;
	else if (SIDE == 0 && XDIRCAM < 0)
		c = NORTH;
	else if (SIDE == 1 && YDIRCAM >= 0)
		c = EAST;
	else
		c = WEST;
	if (SIDE == 1)
		c = c / 2;
	return (c);
}


void	fill_color(t_wolf *wolf)
{
	int		c;
	int		i;

	i = -1;
	while (++i < WINDOW_Y)
	{
		if (i < START)
			c = SKY;
		else if (i > END)
			c = GROUND;
		else
		{
			if (HIT == 1)
				c = fill_wall(wolf);
		}
		pixel_put(wolf, X_1, i, c);
	}
}
