#ifndef CUB3D_H
# define CUB3D_H
# include "minilibX/mlx.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# define mapWidth 24
# define mapHeight 24
# define screenWidth 640
# define screenHeight 48
# define MIN_WALL_HEIGHT 15

typedef	struct	s_texture
{
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			*addr;
	void		*img;
}				t_texture;

typedef struct	s_mlx
{
	void		*ptr;
	void		*window;
	void		*screen;
	char		*screen_data;
	t_texture	*n_img;
	t_texture	*s_img;
	t_texture	*w_img;
	t_texture	*e_img;
	char		*title;
	int			x;
	int			y;
}				t_mlx;

typedef struct	s_player
{
	int			kk;
	//player pos.
	double		x;
	double		y;
	double		x2;//aux
	double		y2;//aux
	//player dir.
	double		alpha;//angulo entre 1,0 y la direccion
	double		dir_x;
	double		dir_y;
	//camera plane.
	double		plane_x;
	double		plane_y;
	//player stats
	int			h;//h modifier for render (jump and crawl)
	double		mov_speed;// = frameTime * 5.0; //the constant value is in squares/second
    double		rot_speed;// = frameTime * 3.0; //the constant value is in radians/second
}				t_player;

typedef struct	s_ray
{
	//ray pos.
	int			x;
	int			y;
	//ray dir.
	double		dir_x;
	double		dir_y;
	//length of ray from current pos to next x or y side.
	double		side_dist_x;
	double		side_dist_y;
	//length of ray from one x or y-side to next x or y-side.
	double		delta_dist_x;// = std::abs(1 / rayDirX);
	double		delta_dist_y;// = std::abs(1 / rayDirY);
	double		perp_wall_dist;
	int			col;//pos in camera plane
	double		wall_x;

	//what direction to step in x or y-direction (either +1 or -1).
	int			step_x;
	int			step_y;

	int			hit; //was there a wall hit?
	int			side; //was a NS or a EW wall hit?
}				t_ray;

typedef struct	s_data
{
	t_mlx		*mlx;
	t_player	*player;
	void		*img;
	int			**map;
	int			map_width;
	int			map_height;
	int			res_x;
	int			res_y;
	char		*n_texture;
	char		*s_texture;
	char		*w_texture;
	char		*e_texture;
	char		*sprite_texture;
	int			floor_color;
	int			ceil_color;
}				t_data;

typedef	struct	s_paint_col
{
	int			line_height;
	int			color;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	int			tex_y;
	double		step;
	double		tex_pos;
	double		wall_x;
}				t_paint_col;

int				ft_render(t_data *data, t_mlx *mlx, t_player *player, int **map);
int				ft_color_switch(t_ray *ray);

double			ft_ray_dist(t_ray *ray, t_player *player);

int				ft_texel_selector(t_texture *texture, t_ray *ray, int col, int row, int draw_end, int draw_start);
void			ft_paint_col(t_ray *ray, t_data *data);
void			ft_init_ray(t_ray *ray, t_player *player, double camera_x);
void			ft_step_calc(t_ray *ray, t_player *player);

int				ft_loop_hook(void *params);
int				ft_key_hook(int keycode, void *params);

int				ft_get_map(char *map, t_data *data);
int				ft_check_line(int *line, int **tab, char *str, t_data *data);
int				ft_check_map_line(int *line, int **tab, char *str, t_data *data);
int				ft_first_line_check(int *line, int **tab, char *str, t_data *data);
int				ft_check_info_line(char *str, t_data *data);

int				ft_check_c(char *str, t_data *data);
int				ft_check_r(char *str, t_data *data);
int				ft_check_s(char *str, t_data *data);
int				ft_check_w(char *str, t_data *data);
int				ft_check_e(char *str, t_data *data);
int				ft_check_n(char *str, t_data *data);
int				ft_check_full(char *str, char c);
int				ft_set_dir_texture(char *str, int i, char **texture);


void			ft_print_data(t_data  *data);
void			ft_atoi_rgb(char *str, int rgb[3]);
void			ft_set_pos(t_player *player, char c, int x, int y);
int				ft_cub_error(void);
int				ft_memory_error(void);
int				ft_map_error(void);


int				ft_in_set(char c, char *set);
int				ft_isdigit(int c);
int				ft_isalpha(int c);
int				ft_isspace(char c);
void			*ft_realloc(void *ptr, int prev_size, int new_size);
void			*ft_calloc(size_t count, size_t size);

int				ft_check_r(char *str, t_data *data);
int				ft_check_n(char *str, t_data *data);
int				ft_check_s(char *str, t_data *data);
int				ft_check_e(char *str, t_data *data);
int				ft_check_w(char *str, t_data *data);
void			ft_atoi_rgb(char *str, int rgb[3]);

void			ft_init_mlx(t_data *data, char *map_name);
void			ft_init_texture(t_mlx *mlx, t_texture *tex, char *parth);
void			ft_init_player(t_player *player, double r_speed, double m_speed);
void			ft_init_data(t_data *data, char *map_name, double r_speed, double m_speed);
int				ft_key_release_hook(int keycode, void *params);

int				ft_atoi(const char *str);
#endif
