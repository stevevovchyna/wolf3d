#include "wolf3d.h"

char	*concat(char *str1, char *str2)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	i = -1;
	while (str1[++i])
		str[i] = str1[i];
	free(str1);
	j = -1;
	while (str2[++j])
		str[i + j] = str2[j];
	str[i + j] = '\0';
	return (str);
}

int		check_borders(char *buffer)
{
	int 	i;
	int		m;
	int		k;

	i = -1;
	while (buffer[++i] != '\n')
		BUF_RET(i);
	m = i - 1;
	k = i + 1;
	while (buffer[i])
	{
		i++;
		BUF_RET(i);
		while (i < ((m + k)))
			i++;
		BUF_RET(i);
		i++;
		m += k;
	}
	while (buffer[--i] != '\n')
		BUF_RET(i);
	return (0);
}

int		check_map(char *buffer)
{
	int	i;

	i = ft_strlen(buffer);
	buffer[i - 1] = '\0';
	i = -1;
	while (buffer[++i])
	{
		if (buffer[i] != '\n' && buffer[i] != '0' && buffer[i] != '1'\
				&& buffer[i] != 'X' && buffer[i] != '\0')
		{
			ft_putendl("error: invalid characters in the file");
			return (-1);
		}
	}
	if (check_borders(buffer) == -1)
	{
		ft_putendl("error: your map must have descent rectangular borders");
		return (-1);
	}
	return (0);
}

char	*read_map(char *s, int *lines_number)
{
	int		fd;
	char	*buffer;
	char	*line;

	buffer = ft_strnew(0);
	if ((fd = open(s, O_RDONLY)) == -1)
	{
		ft_putendl(ft_strjoin("error: ", strerror(errno)));
		return (NULL);
	}
	while (get_next_line(fd, &line) > 0 && (*lines_number)++ > -1)
	{
		buffer = concat(concat(buffer, line), "\n");
		ft_strdel(&line);
	}
	if (check_map(buffer) == -1)
		return (NULL);
	if (close(fd) == -1)
	{
		ft_putendl(ft_strjoin("error: ", strerror(errno)));
		return (NULL);
	}
	return (buffer);
}

t_wolf	*init(char *s)
{
	t_wolf	*wolf;
	char	*buffer;
	char	*name;

	name = ft_strjoin("wolf3d :", s);
	if (!(wolf = (t_wolf *)malloc(sizeof(t_wolf))))
		return (NULL);
	LNUMBER = 0;
	MLX = mlx_init();
	IMG = mlx_new_image(MLX, WINDOW_X, WINDOW_Y);
	WIN = mlx_new_window(MLX, WINDOW_X, WINDOW_Y, name);
	free(name);
	ADDR = mlx_get_data_addr(IMG, &BPP, &LINESIZE,
			&ENDIAN);
	buffer = read_map(s, &(LNUMBER));
	if ((KARTA = write_map(buffer, LNUMBER, 0, wolf)) == NULL)
		return (NULL);
	free(buffer);
	XPLN = 0.0;
	YPLN = 1.23;
	WHEIGHT = 2.0;
	return (wolf);
}
