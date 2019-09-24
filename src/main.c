#include "wolf3d.h"

char	**wrt_n_init(char *buf, char **karta, int l_n, int j, t_wolf *wolf)
{
	INT2(i, 0, k, -1);
	while (buf[++k] != '\0' && j < l_n)
	{
		i = 0;
		if (!(karta[j] = (char *)malloc(sizeof(char) * line_length(buf, k))))
			return (NULL);
		while (buf[k] != '\n' && buf[k] != '\0')
		{
			karta[j][i] = buf[k];
			if (karta[j][i] == 'X')
			{
				INIT5(XPOS, j, YPOS, i, XDIR, -1, SPRNT, 0, YPOSMAP, i);
				INIT4(YDIR, 0, MOVSPD, 0.2, ROTSPD, 0.08, XPOSMAP, j);
			}
			INCREMENTO2(k, i);
		}
		karta[j][i] = '\0';
		j++;
		LENGTH = i;
	}
	return (karta);
}

char	**write_map(char *buffer, int lines_number, int j, t_wolf *wolf)
{
	char	**karta;

	if (!buffer || !(karta = (char **)malloc(sizeof(char *) * 
		lines_number * 1000)))
		return (NULL);
	karta = wrt_n_init(buffer, karta, lines_number, j, wolf);
	if (!XPOS || !YPOS)
	{
		ft_putendl("error : player not found on the map");
		return (NULL);
	}
	return (karta);
}

void	dooom(t_wolf *wolf)
{
	X_1 = -1;
	while (++X_1 < WINDOW_X)
	{
		display_init(wolf);
		ray(wolf);
		fill_color(wolf);
	}
	display_radar(wolf);
	mlx_put_image_to_window(MLX, WIN, IMG, 0, 0);
	mlx_hook(WIN, 2, (1L << 0), key_press, wolf);
	mlx_loop(MLX);
	mlx_destroy_window(MLX, WIN);
}

int			check_extension(char *s)
{
	char	*pointer;
	int		result;

	pointer = ft_strrchr(s, '.');
	if (pointer == NULL)
	{
		return (1);
	}
	result = ft_strcmp(pointer, ".wolf");
	if (result == 0)
	{
		return (0);
	}
	else
	{
		return (1);
	}
}

int			main(int argc, char **argv)
{
	t_wolf	*wolf;

	if (argc == 2 && argv[1])
	{
		if (check_extension(argv[1]))
		{
			ft_putendl("error: map file should have a '.wolf' extension");
			return (0);
		}
		if ((wolf = init(argv[1])) == NULL)
			return (0);
		dooom(wolf);
	}
	return (0);
}
