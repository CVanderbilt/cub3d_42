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

typedef	struct		s_texture
{
	int				offset;
	int				animated;
	int				a_directions;
	int				a_states;
	int				real_width;
	int				real_height;
	double			width;
	double			height;
	int				bpp;
	int				size_line;
	int				*addr;
	void			*img;
}					t_texture;

typedef struct		s_mlx
{
	void			*ptr;
	void			*window;
	void			*screen;
	char			*screen_data;
	t_texture		*n_img;
	t_texture		*s_img;
	t_texture		*w_img;
	t_texture		*e_img;
	t_texture		*skybox;
	//t_texture	*floor;
	//t_texture	*sprite1;
	char			*title;
	int				x;
	int				y;
}					t_mlx;

typedef struct		s_player
{
	int				move_them;

	int				health;
	int				ammo;
	int				kk;
	//player pos.
	double			x;
	double			y;
	double			x2;//aux
	double			y2;//aux
	//player dir.
	//sprites[0].id = 1;	
	double			dir_x;
	double			dir_y;
	//camera plane.
	double			plane_x;
	double			plane_y;
	//player stats
	int				moving_forward;
	int				moving_backward;
	int				moving_left;
	int				moving_right;
	int				rotating_right;
	int				rotating_left;
	double			mov_speed;// = frameTime * 5.0; //the constant value is in squares/second
    double			rot_speed;// = frameTime * 3.0; //the constant value is in radians/second
}					t_player;

/*typedef struct		s_ext_sprite
{
	double			dir_x;
	double			dir_y;
	int				state;
}					t_ext_sprite;*/

typedef struct		s_sprite
{
	//t_texture		*texture;
	//char			*texture_path;
	int				texture;
	double			x;
	double			y;
	double			back_x;
	double			back_y;
	double			dir_x;
	double			dir_y;
	int				value;
	int				type;
	int				state; //0 quieto o random, 1 persigue, 2 disparando, 3 muerto
	int				shoot;
	int				moved;
	int				comprobador;
	//t_ext_sprite	*ext;
}					t_sprite;

typedef struct		s_ray
{
	//ray pos.
	int				x;
	int				y;
	//ray dir.
	double			dir_x;
	double			dir_y;
	//length of ray from current pos to next x or y side.
	double			side_dist_x;
	double			side_dist_y;
	//length of ray from one x or y-side to next x or y-side.
	double			delta_dist_x;// = std::abs(1 / rayDirX);
	double			delta_dist_y;// = std::abs(1 / rayDirY);
	double			perp_wall_dist;
	int				col;//pos in camera plane
	double			wall_x;

	//what direction to step in x or y-direction (either +1 or -1).
	int				step_x;
	int				step_y;

	int				hit; //was there a wall hit?
	int				side; //was a NS or a EW wall hit?
}					t_ray;

typedef struct		s_arrow
{
	int				x;  //al estar en un array2d sobra
	int				y;  //al estar en un array2d sobra
	int				dir_x;
	int				dir_y;
	int				used;
}					t_arrow;

typedef struct		s_coordinate
{
	int				x;
	int				y;
}					t_coordinate;

typedef struct		s_data
{
	t_mlx			*mlx;
	t_player		*player;

	int				animation_num;
	int				animation_cycle;

	t_texture		soldier_anim[5];
	t_texture		*soldier_shoot;

	t_texture		*hud;
	t_texture		weapon[5];
	int				shooting;
	int				weapon_state;
	t_texture		numbers[10];

	t_texture		*healthbar;
	int				sprite_tex_num;
	t_texture		*sprite_tex_buffer;
	
	int				sprites_num;
	t_sprite		*sprite_buffer;

	//void		*img;
	int				**map;
	int				**collision_map;
	t_arrow			**arrow_map;
	t_coordinate	*arrow_history;

	int				map_width;
	int				map_height;
	int				res_x;
	int				res_y;
	char			*n_texture;
	char			*s_texture;
	char			*w_texture;
	char			*e_texture;
	//char		*sprite1;
	int				floor_color;
	int				ceil_color;
	double			*buffer_z;
}					t_data;

typedef	struct		s_paint_col
{
	int				line_height;
	int				color;
	int				draw_s;
	int				draw_end;
	int				tex_x;
	int				tex_y;
	int				mul;
	double			step;
	double			tex_pos;
	double			wall_x;
	t_texture		*tex;
	int				*img;
}					t_paint_col;

typedef struct		s_check_line
{
	int				fd;
	int				finished;
	char			*str;
}					t_check_line;

typedef struct		s_check_map_line
{
	int				i;
	int				count;
	int				last_element;
}					t_check_map_line;

typedef struct		s_first_line_check
{
	int				i;
	int				count;
}					t_first_line_check;

typedef struct		s_paint_one_sprite
{
	t_player		*p;
	double			i_t;
	double			s_x;
	double			s_y;
	double			tf_x;
	double			tf_y;
	int				ss_x;
	int				sprite_h;
	int				s_w;
	int				start_y;
	int				end_y;
	int				start_x;
	int				end_x;
	int				c;
	int				t_x;
	int				t_y;
	t_texture		*t;
	int				*img;
	int				*screen;
	int				y;
	int				col;
	int				d;
}					t_pos;

typedef struct		s_get_sprite_texture
{
	t_player		*p;
	t_texture		*t;
	double			a;
	double			sector;
	int				x_grid;
}					t_gst;

typedef struct		s_paint_sky_col
{
	t_texture		*t;
	int				*sky_img;
	float			a;
	int				i;
	int				j;
	int				offset;
	float			kk;
}					t_paint_sky_col;

typedef struct		s_update_hud
{
	int				screen_x;
	int				screen_y;
	int				color;
	double			x;
	double			y;
	double			x_step;
	double			y_step;
	double			x_max;
	t_texture		*t;
	int				*img;
	int				*screen;
}					t_update_hud;

typedef struct		s_lifebar
{
	t_player		*p;
	int				mod_y;
	int				mod_x;
	int				start_x;
	int				start_y;
	int				end_x;
	int				end_y;
	int				health_ptg;
	int				*img;
}					t_lifebar;

typedef struct		s_coordinate_pointer
{
	int				x;
	int				y;
	void			*p;
}					t_coordinate_pointer;

typedef struct		s_move_soldiers
{
	int				i;
	double			f_x;
	double			f_y;
}					t_move_soldiers;

typedef struct		s_try_shoot_params
{
	t_data 			*d;
	double			x_dir;
	double			y_dir;
	double			x;
	double			y;
	double			x_dest;
	double			y_dest;
}					t_try_shoot_params;

typedef struct		s_try_params
{
	t_data			*data;
	int				dir_x;
	int				dir_y;
	int				x;
	int				y;
}					t_try_params;

void				ft_print_data(t_data  *data);

int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isspace(char c);

void				ft_init_mlx(t_data *data, char *map_name);
void				ft_init_texture(t_mlx *mlx, t_texture *tex, char *parth);
void				ft_init_player(t_player *player, double r_speed, double m_speed);
void				ft_init_data(t_data *data, char *map_name, double r_speed, double m_speed, int cycles);

void				ft_init_soldier(t_data *data);

int					ft_atoi(const char *str);

//map_reader
void				*ft_calloc(size_t count, size_t size);

void				*ft_realloc(void *ptr, int prev_size, int new_size);

int					ft_memory_error(void);
int					ft_map_error(void);
int					ft_cub_error(void);

int					ft_in_set(char c, char *set);

void				ft_set_pos(t_player *player, char c, int x, int y);
int					ft_check_full(char *str, char c);
int					ft_set_dir_texture(char *str, int i, char **texture);
char				*ft_get_text(char *str);

int					ft_check_n(char *str, t_data *data);
int					ft_check_e(char *str, t_data *data);
int					ft_check_w(char *str, t_data *data);
int					ft_check_s(char *str, t_data *data);

int					ft_check_r(char *str, t_data *data);
int					ft_check_c(char *str, t_data *data);
int					ft_check_t(char *str, t_data *data);

int					ft_sprite_extra_data_precheck(char *str, t_sprite *s, int i);
void				ft_sprite_extra_data(char *str, t_sprite *sprite, int i);
int					ft_set_sprite_data_precheck(char *str, t_sprite *sprite);
void				ft_set_sprite_data(char *str, t_sprite *sprite);
int					ft_set_new_sprite(char *str, t_data *data);

int					ft_set_animation_data_precheck(char *str, t_texture *t);
void				ft_set_animation_data(char *str, t_data *data, t_texture *t);
void				ft_set_sprite_tex_data(char *str, t_data *data, t_texture *t);

void				ft_atoi_rgb(char *str, int rgb[3]);

int					ft_check_info_line(char *str, t_data *data);
int					ft_first_line_check(int *line, int **tab, char *str, t_data *d);
int					ft_check_map_line(int *line, int **tab, char *str, t_data *data);
int					ft_check_line(int *line, int **tab, char *str, t_data *data);
int					ft_get_map(char *map, t_data *data);
//fin map_reader

//tst_ray
void			ft_step_calc_2(t_ray *ray, double x, double y);
void			ft_step_calc(t_ray *ray, t_player *player);
double			ft_ray_dist(t_ray *ray, t_player *player);
void			ft_ray_side_dist(t_ray *ray);
int				ft_render(t_data *data, t_mlx *mlx, t_player *player, int **map);

void			ft_init_ray(t_ray *ray, t_player *player, double camera_x);
void			ft_paint_sky_col(t_ray *ray, t_data *d, t_paint_col *ft, int *img);
void			ft_paint_col(t_ray *ray, t_data *data);

t_texture		*ft_switch_texture(t_data *data, t_ray *ray);
int				ft_tex_xcalc(t_ray *ray, t_texture *tex, double wall_x);
int				ft_get_gridx(double a);
int				ft_get_gridy(t_data *data, t_sprite *s, int states);
t_texture		*ft_select_moving_tex(t_data *data);

t_texture		*ft_get_sprite_texture(t_data *data, t_sprite *s);
void			ft_paint_one_sprite_aux(t_data *data, t_sprite *sprite, t_pos *f);
void			ft_paint_one_sprite(t_data *data, t_sprite *sprite);
void			ft_sort_sprites(int *orden, double *dist, int num);
void			ft_paint_sprites(t_data *data);
//fin tst_ray

//events
int				ft_key_release_hook(int keycode, void *params);
int				ft_loop_hook(void *params);
int				ft_key_hook(int keycode, void *params);

void			ft_lifebar(t_data *data);
void			ft_update_hud_aux(t_data *data, t_update_hud *ft);
void			ft_update_hud(t_data *data);

void			ft_free_sprites(t_data *data);
void			ft_free_mlx(t_mlx *mlx);
void			ft_free_and_exit(t_data *data);

void			ft_free_map(t_data *data);
void			ft_free_texture(t_data *data, t_texture *t);
void			ft_free_textures(t_data *data);

void			ft_reset_arrow_map(t_data *data);
void			ft_set_surrounding(t_data *d, t_coordinate *c, int index, int *arrows);
void			ft_update_arrow_map(t_data *data);
void			ft_update_extra_maps(t_data *data);

int				ft_try(t_try_params *p);
void			ft_set_etile(t_try_params *p, int *arrows, t_coordinate *c);
void			ft_set_stile(t_try_params *p, int *arrows, t_coordinate *c);
void			ft_set_wtile(t_try_params *p, int *arrows, t_coordinate *c);
void			ft_set_ntile(t_try_params *p, int *arrows, t_coordinate *c);

void			ft_sprite_advance(t_data *data, int code, double step, t_sprite *s);
void			ft_activate_sprite(t_data *data, t_sprite *s);
void			ft_move_soldiers(t_data *d);
int				ft_is_soldier(t_data *data, int x, int y);

void			ft_check_movement(t_data *data, int keycode, int state);
int				ft_can_walk(t_data *data, int x, int y);
int				ft_player_advance(t_data *data, int code, double step);
int				ft_player_rotate(t_player *player, double a, int code);
int				ft_move(t_data *data, t_player *player);

double			ft_init_shoot_ray(t_ray *ray, t_try_shoot_params *p);
int				ft_try_shoot(t_try_shoot_params *p);
void			ft_shoot_succes(t_data *d, t_sprite *s);
void			ft_shoot_fail(t_data *d, t_sprite *s, double f_x, double f_y);
void			ft_init_ts_param(t_data *d, t_sprite *s, t_try_shoot_params *p);
//fin events
#endif
