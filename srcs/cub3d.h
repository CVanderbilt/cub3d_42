/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:03:00 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/05 14:44:59 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "cub3d_structs.h"
# include "../minilibX/mlx.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

/*
**					utils
*/
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isspace(char c);
int			ft_strcmp(char *str1, char *str2);
int			ft_atoi(const char *str);
void		ft_atoi_rgb(char *str, int rgb[3]);
void		ft_putstr(char *str);
int			ft_in_set(char c, char *set);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_itoa(int n);
int			ft_check_extension(char *str, char *ext);
int			ft_open_check(char *map, int flags);
/*
**					map_reader
*/
void		*ft_calloc(size_t count, size_t size);
void		*ft_realloc(void *ptr, int prev_size, int new_size);
int			ft_memory_error(void);
int			ft_map_error(void);
int			ft_cub_error(void);
int			ft_arg_error(void);
int			ft_other_error(char *str, char *str2);
void		ft_set_pos(t_player *player, char c, int x, int y);
int			ft_check_full(char *str, char c);
int			ft_set_dir_texture(char *str, int i, char **texture);
char		*ft_get_text(char *str);
int			ft_check_n(char *str, t_data *data);
int			ft_check_e(char *str, t_data *data);
int			ft_check_w(char *str, t_data *data);
int			ft_check_s(char *str, t_data *data);
int			ft_check_r(char *str, t_data *data);
int			ft_check_c(char *str, t_data *data);
int			ft_check_t(char *str, t_data *data);
int			ft_sprite_extra_data_precheck(char *str, t_sprite *s, int i);
void		ft_sprite_extra_data(char *str, t_sprite *sprite, int i);
int			ft_set_sprite_data_precheck(char *str, t_sprite *sprite);
void		ft_set_sprite_data(char *str, t_sprite *sprite);
int			ft_set_new_sprite(char *str, t_data *data);
int			ft_set_animation_data_precheck(char *str, t_texture *t);
void		ft_set_animation_data(char *str, t_data *data, t_texture *t);
void		ft_set_sprite_tex_data(char *str, t_data *data, t_texture *t);
int			ft_check_info_line(char *str, t_data *data);
int			ft_first_line_check(int *line, int **tab, char *str, t_data *d);
int			ft_check_map_line(int *line, int **tab, char *str, t_data *data);
int			ft_check_line(int *line, int **tab, char *str, t_data *data);
int			ft_get_map(char *map, t_data *data);
int			ft_set_map_sprite(int x, int y, t_data *data);
int			ft_check_info_line(char *str, t_data *data);
void		ft_validate_coordinate(t_coordinate c, int s, int **t, int c1);
void		ft_check_space_valid(int **tab, int x, int y, int size);
void		ft_fill_line(t_check_map_line *ft, t_data *data, int *l);
/*
**					render
*/
void		ft_step_calc_2(t_ray *ray, double x, double y);
void		ft_step_calc(t_ray *ray, t_player *player);
double		ft_ray_dist(t_ray *ray, t_player *player);
void		ft_ray_side_dist(t_ray *ray);
void		ft_render(t_data *data, t_mlx *mlx, t_player *player, int **map);
void		ft_init_ray(t_ray *ray, t_player *player, double camera_x);
void		ft_paint_sky_col(t_ray *ray, t_data *d, t_paint_col *ft, int *img);
int			ft_redder(int color, double dst);
void		ft_paint_col(t_ray *ray, t_data *data);
t_texture	*ft_switch_texture(t_data *data, t_ray *ray);
int			ft_tex_xcalc(t_ray *ray, t_texture *tex, double wall_x);
int			ft_get_gridx(double a);
int			ft_get_gridy(t_data *data, t_sprite *s, int states);
t_texture	*ft_select_moving_tex(t_data *data);
t_texture	*ft_get_sprite_texture(t_data *data, t_sprite *s);
void		ft_paint_one_sprite_aux(t_data *data, t_sprite *sprite, t_pos *f);
void		ft_paint_one_sprite(t_data *data, t_sprite *sprite);
void		ft_sort_sprites(int *orden, double *dist, int num);
void		ft_paint_sprites(t_data *data);
/*
**					events
*/
int			ft_key_release_hook(int keycode, void *params);
void		ft_new_level(t_data *data, char *str);
void		ft_dead(t_data *data);
int			ft_loop_hook(void *params);
int			ft_key_hook(int keycode, void *params);
void		ft_lifebar(t_data *data);
void		ft_update_hud_aux(t_data *data, t_update_hud *ft);
void		ft_update_hud(t_data *data);
void		ft_free_sprites(t_data *data);
void		ft_free_mlx(t_mlx *mlx);
void		ft_free_all(t_data *data);
int			ft_free_and_exit(void *data);
void		ft_free_map(t_data *data);
void		ft_free_texture(t_data *data, t_texture *t);
void		ft_free_textures(t_data *data);
void		ft_reset_arrow_map(t_data *data);
void		ft_set_surrounding(t_data *d, t_coordinate *c, int ix, int *arrows);
void		ft_update_arrow_map(t_data *data);
void		ft_update_extra_maps(t_data *data);
int			ft_try(t_try_params *p);
void		ft_set_etile(t_try_params *p, int *arrows, t_coordinate *c);
void		ft_set_stile(t_try_params *p, int *arrows, t_coordinate *c);
void		ft_set_wtile(t_try_params *p, int *arrows, t_coordinate *c);
void		ft_set_ntile(t_try_params *p, int *arrows, t_coordinate *c);
void		ft_sprite_advance(t_data *data, int code, double step, t_sprite *s);
void		ft_activate_sprite(t_data *data, t_sprite *s);
void		ft_move_soldiers(t_data *d);
int			ft_is_soldier(t_data *data, int x, int y);
void		ft_check_movement(t_data *data, int keycode, int state);
int			ft_can_walk(t_data *data, int x, int y);
int			ft_player_advance(t_data *data, int code, double step);
int			ft_player_rotate(t_player *player, double a, int code);
int			ft_move(t_data *data, t_player *player);
double		ft_init_shoot_ray(t_ray *ray, t_try_shoot_params *p);
int			ft_try_shoot(t_try_shoot_params *p);
void		ft_shoot_succes(t_data *d, t_sprite *s);
void		ft_shoot_fail(t_data *d, t_sprite *s, double f_x, double f_y);
void		ft_init_ts_param(t_data *d, t_sprite *s, t_try_shoot_params *p);
/*
**					main
*/
void		ft_init_player(t_player *p, double r_s, double m_s);
void		ft_init_mlx(t_data *data, char *map_name);
void		ft_init_extra_maps(t_data *data);
void		ft_init_data(t_data *d, char *map, double rsp, double msp);
void		ft_loop(t_data *data);
char		*ft_init_texture_aux(t_init_texture *p, t_texture *t);
void		ft_init_texture(t_mlx *mlx, t_texture *t, char *path);
void		ft_init_weapon(t_data *data);
void		ft_init_textures(t_data *data);
void		ft_init_extra_animations(t_data *data);
void		ft_init_soldier(t_data *data);
/*
**					bmp.c
*/
int			take_screenshot(t_data *data);
#endif
