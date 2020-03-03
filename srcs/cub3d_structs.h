/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:52:54 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/03 17:08:34 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

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
	double			x;
	double			y;
	double			x2;
	double			y2;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	int				moving_forward;
	int				moving_backward;
	int				moving_left;
	int				moving_right;
	int				rotating_right;
	int				rotating_left;
	double			mov_speed;
	double			rot_speed;
}					t_player;
typedef struct		s_sprite
{
	int				texture;
	double			x;
	double			y;
	double			back_x;
	double			back_y;
	double			dir_x;
	double			dir_y;
	int				value;
	int				type;
	int				state;
	int				shoot;
	int				moved;
	int				comprobador;
}					t_sprite;
typedef struct		s_ray
{
	int				x;
	int				y;
	double			dir_x;
	double			dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				col;
	double			wall_x;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
}					t_ray;
typedef struct		s_arrow
{
	int				x;
	int				y;
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
	int				screenshot;
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
	t_data			*d;
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
typedef struct		s_init_texture
{
	t_mlx			*mlx;
	t_texture		*t;
	char			*path;
	int				fd;
	int				fd_old;
	int				e;
	int				w;
	int				h;
}					t_init_texture;
#endif
