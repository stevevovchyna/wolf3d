#include "wolf3d.h"

void	display_init(t_wolf *wolf)
{
	HIT = 0;
	SIDE = 0;
	XPOSCAM = XPOS;
	YPOSCAM = YPOS;
	XMAP = (int)XPOSCAM;
	YMAP = (int)YPOSCAM;
	X = 2 * X_1 / (double)WINDOW_X - 1;
	XDIRCAM = XDIR + XPLN * X;
	YDIRCAM = YDIR + YPLN * X;
	DELTADISTX = sqrt(1 + pow(YDIRCAM / XDIRCAM, 2));
	DELTADISTY = sqrt(1 + pow(XDIRCAM / YDIRCAM, 2));
}

int		line_length(char *buffer, int k)
{
	int	i;

	i = 0;
	while (buffer[k++] != '\n' && buffer[k] != '\0')
		i++;
	return (i);
}

void	wall_check(t_wolf *wolf)
{
	while (HIT != 1 && YMAP > 0 && YMAP < line_length(KARTA[XMAP], 0) && XMAP > 0 && XMAP <= LNUMBER)
	{
		if (SIDEDISTX < SIDEDISTY)
		{
			SIDE = 0;
			XMAP += STEPX;
			SIDEDISTX += DELTADISTX;
		}
		else
		{
			SIDE = 1;
			YMAP += STEPY;
			SIDEDISTY += DELTADISTY;
		}
		if (KARTA[XMAP][YMAP] == '1')
			HIT = 1;
	}
}

void	walk(t_wolf *wolf)
{
	if (YDIRCAM < 0)
	{
		STEPY = -1;
		SIDEDISTY = (YPOSCAM - (double)YMAP) * DELTADISTY;
	}
	else
	{
		STEPY = 1;
		SIDEDISTY = ((double)YMAP + 1.0 - YPOSCAM) * DELTADISTY;
	}
	if (XDIRCAM < 0)
	{
		STEPX = -1;
		SIDEDISTX = (XPOSCAM - (double)XMAP) * DELTADISTX;
	}
	else
	{
		STEPX = 1;
		SIDEDISTX = ((double)XMAP + 1.0 - XPOSCAM) * DELTADISTX;
	}
}

void	ray(t_wolf *wolf)
{
	walk(wolf);
	wall_check(wolf);
	WDIST = SIDE == 0 ? fabs((XMAP - XPOSCAM + (1 - STEPX) / 2) / XDIRCAM) :
		fabs((YMAP - YPOSCAM + (1 - STEPY) / 2) / YDIRCAM);
	WDIST = WDIST <= 0.05 ? WDIST = 0.05 : WDIST;
	HEIGHT = fabs(WINDOW_Y / WDIST);
	START = (START = -(HEIGHT) / WHEIGHT + WINDOW_Y / 2) < 0 ? 0 : START;
	END = (END = HEIGHT / 2 + WINDOW_Y / 2) >= WINDOW_Y ? WINDOW_Y - 1 : END;
}
