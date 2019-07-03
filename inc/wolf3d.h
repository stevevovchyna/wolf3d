#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <errno.h>

# define EAST 0xCE127A
# define NORTH 0x12C996
# define SOUTH 0x12C0CE
# define WEST 0xFFFF00
# define SKY 0x0E5B94
# define GROUND 0x616967
# define WHITE 0x000000
# define RED 0xFF0000
# define BLACK 0xFFFFFF

# define UPARROW 126
# define LEFTARROW 123
# define RIGHTARROW 124
# define DOWNARROW 125
# define W_BUTTON 13
# define S_BUTTON 1
# define D_BUTTON 2
# define A_BUTTON 0
# define MINUS 27
# define PLUS 24
# define ESC 53
# define SHIFT 257

# define WINDOW_X 1280
# define WINDOW_Y 720

# define X wolf->x
# define END wolf->end
# define HIT wolf->hit
# define X_1 wolf->x_1
# define MLX wolf->mlx
# define BPP wolf->bpp
# define WIN wolf->win
# define IMG wolf->img
# define HEIGHT wolf->h
# define SIDE wolf->side
# define ADDR wolf->addr
# define XMAP wolf->x_map
# define YMAP wolf->y_map
# define XPOS wolf->x_pos
# define YPOS wolf->y_pos
# define XDIR wolf->x_dir
# define YDIR wolf->y_dir
# define KARTA wolf->karta
# define START wolf->start
# define STEPX wolf->step_x
# define STEPY wolf->step_y
# define XPLN wolf->x_plane
# define YPLN wolf->y_plane
# define SPRNT wolf->sprint
# define LENGTH wolf->length
# define ENDIAN wolf->endian
# define ROTSPD wolf->rot_speed
# define MOVSPD wolf->move_speed
# define YPOSMAP wolf->y_pos_map
# define XPOSMAP wolf->x_pos_map
# define XDIRCAM wolf->x_dir_cam
# define YDIRCAM wolf->y_dir_cam
# define XPOSCAM wolf->x_pos_cam
# define YPOSCAM wolf->y_pos_cam
# define LINESIZE wolf->line_size
# define WHEIGHT wolf->wall_height
# define WDIST wolf->wall_distance
# define LNUMBER wolf->lines_number
# define SIDEDISTX wolf->side_distance_x
# define SIDEDISTY wolf->side_distance_y
# define DELTADISTX wolf->delta_distance_x
# define DELTADISTY wolf->delta_distance_y


# define BUF_RET(i) if (buffer[i] != '1') { return (-1); }
# define INT2(a, b, c, d) int a = b; int c = d;
# define INIT5(a, b, c, d, e, f, g, h, i, j) a = b; c = d; e = f; g = h; i = j;
# define INIT4(a, b, c, d, e, f, g, h) a = b; c = d; e = f; g = h;
# define INIT3(a, b, c, d, e, f) a = b; c = d; e = f;
# define INCREMENTO2(a, b) a++; b++;

typedef struct	s_wolf
{
	double		x;
	int			h;
	int			bpp;
	int			end;
	int			hit;
	void		*mlx;
	void		*win;
	void		*img;
	int			x_1;
	int			side;
	char		*addr;
	int			x_map;
	int			y_map;

	double		x_dir;
	double		y_dir;

	double		x_pos;
	double		y_pos;
	double		x_pos_map;
	double		y_pos_map;

	int			start;
	int			length;
	int			endian;
	int			sprint;

	int			step_x;
	int			step_y;

	char		**karta;
	
	double		x_plane;
	double		y_plane;

	double		x_pos_cam;
	double		y_pos_cam;

	double		x_dir_cam;
	double		y_dir_cam;

	double		rot_speed;
	int			line_size;
	double		move_speed;
	double		wall_height;
	int			lines_number;
	double		wall_distance;

	double		side_distance_x;
	double		side_distance_y;

	double		delta_distance_x;
	double		delta_distance_y;

}				t_wolf;

void	dooom(t_wolf *wolf);
char	**write_map(char *buffer, int lines_number, int j, t_wolf *wolf);
char	**wrt_n_init(char *buf, char **karta, int l_n, int j, t_wolf *wolf);

char	*concat(char *str1, char *str2);
int		check_borders(char *buffer);
int		check_map(char *buffer);
char	*read_map(char *s, int *lines_number);
t_wolf	*init(char *s);

void	pixel_put(t_wolf *wolf, int x, int y, int c);
void	radar_dot(t_wolf *wolf, int x, int y, int color);
void	display_radar(t_wolf *wolf);
int		fill_wall(t_wolf *wolf);
void	fill_color(t_wolf *wolf);

void	display_init(t_wolf *wolf);
int		line_length(char *buffer, int k);
void	wall_check(t_wolf *wolf);
void	walk(t_wolf *wolf);
void	ray(t_wolf *wolf);

void	camera_rotator(int keycode, double dir,	double plane, t_wolf *wolf);
void	walk_sideways(int keycode, t_wolf *wolf);
void	fast_mode(int keycode, t_wolf *wolf);
void	move(int keycode, t_wolf *wolf);
int		key_press(int keycode, t_wolf *wolf);

#endif
