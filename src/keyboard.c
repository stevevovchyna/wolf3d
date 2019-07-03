#include "wolf3d.h"

void	camera_rotator(int keycode, double dir,	double plane, t_wolf *wolf)
{
	if (keycode == LEFTARROW)
	{
		XDIR = XDIR * cos(ROTSPD) - YDIR * sin(ROTSPD);
		YDIR = dir * sin(ROTSPD) + YDIR * cos(ROTSPD);
		XPLN = XPLN * cos(ROTSPD) - YPLN * sin(ROTSPD);
		YPLN = plane * sin(ROTSPD) + YPLN * cos(ROTSPD);
	}
	if (keycode == RIGHTARROW)
	{
		XDIR = XDIR * cos(-ROTSPD) - YDIR * sin(-ROTSPD);
		YDIR = dir * sin(-ROTSPD) + YDIR * cos(-ROTSPD);
		XPLN = XPLN * cos(-ROTSPD) - YPLN * sin(-ROTSPD);
		YPLN = plane * sin(-ROTSPD) + YPLN * cos(-ROTSPD);
	}
}

void	walk_sideways(int keycode, t_wolf *wolf)
{
	if (keycode == D_BUTTON)
	{
		if (KARTA[(int)(XPOS + XPLN * MOVSPD)][(int)(YPOS)] == '0' ||
			KARTA[(int)(XPOS + XPLN * MOVSPD)][(int)(YPOS)] != '1')
			XPOS += XPLN * MOVSPD;
		if (KARTA[(int)(XPOS)][(int)(YPOS + YPLN * MOVSPD)] == '0' ||
			KARTA[(int)(XPOS)][(int)(YPOS + YPLN * MOVSPD)] != '1')
			YPOS += YPLN * MOVSPD;
	}
	if (keycode == A_BUTTON)
	{
		if (KARTA[(int)(XPOS - XPLN * MOVSPD)][(int)(YPOS)] == '0' ||
			KARTA[(int)(XPOS - XPLN * MOVSPD)][(int)(YPOS)] != '1')
			XPOS -= XPLN * MOVSPD;
		if (KARTA[(int)(XPOS)][(int)(YPOS - YPLN * MOVSPD)] == '0' ||
			KARTA[(int)(XPOS)][(int)(YPOS - YPLN * MOVSPD)] != '1')
			YPOS -= YPLN * MOVSPD;
	}
}

void	fast_mode(int keycode, t_wolf *wolf)
{
	walk_sideways(keycode, wolf);
	if (keycode == SHIFT)
	{
		if (SPRNT == 0)
		{
			MOVSPD = 0.4;
			SPRNT = 1;
		}
		else
		{
			MOVSPD = 0.2;
			SPRNT = 0;
		}
	}
	X_1 = -1;
	while (++X_1 < WINDOW_X)
	{
		display_init(wolf);
		ray(wolf);
		fill_color(wolf);
	}
	display_radar(wolf);
	mlx_put_image_to_window(MLX, WIN, IMG, 0, 0);
}

void	move(int keycode, t_wolf *wolf)
{
	if (keycode == UPARROW || keycode == W_BUTTON)
	{
		if (KARTA[(int)(XPOS + XDIR * MOVSPD)][(int)(YPOS)] != '1')
			XPOS += XDIR * MOVSPD;
		if (KARTA[(int)(XPOS)][(int)(YPOS + YDIR * MOVSPD)] != '1')
			YPOS += YDIR * MOVSPD;
	}
	if (keycode == DOWNARROW || keycode == S_BUTTON)
	{
		if (KARTA[(int)(XPOS - XDIR * MOVSPD)][(int)(YPOS)] != '1')
			XPOS -= XDIR * MOVSPD;
		if (KARTA[(int)(XPOS)][(int)(YPOS - YDIR * MOVSPD)] != '1')
			YPOS -= YDIR * MOVSPD;
	}
	if (keycode == MINUS)
		WHEIGHT = (WHEIGHT < 120) ? WHEIGHT + 0.5 : WHEIGHT;
	if (keycode == PLUS)
		WHEIGHT = (WHEIGHT > 0.5) ? WHEIGHT - 0.5 : WHEIGHT;
	if (keycode == 4)
	{
		INIT4(XPOS, XPOSMAP, YPOS, YPOSMAP, XDIR, -1, YDIR, 0);
		INIT3(XPLN, 0.0, YPLN, 1.23, WHEIGHT, 2.0);
	}
	if (keycode == ESC)
	{
		system("leaks wolf3d");
		exit(1);
	}
}

int		key_press(int keycode, t_wolf *wolf)
{
	move(keycode, wolf);
	camera_rotator(keycode, XDIR, XPLN, wolf);
	fast_mode(keycode, wolf);
	return (0);
}
