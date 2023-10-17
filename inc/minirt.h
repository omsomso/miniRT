/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:43:45 by fcullen           #+#    #+#             */
/*   Updated: 2023/10/13 17:27:49 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>

# include "../libft/libft.h"
# include "../mlx/mlx.h"

# include "types.h"
# include "parser.h"
# include "gui.h"
# include "math.h"
# include "color.h"

# define WIN_HEIGHT 480
# define WIN_WIDTH 640
# define MAX_RECURSION_DEPTH 3
# define NUM_SAMPLES 2
# define SPECULAR_EXP 100

# define EVENT_KEYPRESS 2
# define EVENT_KEYRELEASE 3
# define EVENT_DESTROY 17

# define KEY_ESC 53
# define KEY_RIGHT	124
# define KEY_LEFT	123
# define KEY_DOWN	125
# define KEY_UP		126
# define KEY_W	13
# define KEY_A	0
# define KEY_S	1
# define KEY_D	2
# define KEY_Q	12
# define KEY_E	14
# define KEY_ENTER	36

# define GUI_MAX_WIDTH 700
# define GUI_EL_WIDTH 100
# define GUI_EL_HEIGHT 110
# define GUI_EL_MARGIN 10
# define GUI_EL_PAR_HEIGHT 10
# define GUI_EL_PAR_OFFSET 1
// gui element data margin
# define DM 40

# define MOD_POS 0.2
# define MOD_RADIUS 0.05
# define MOD_FOV 1
# define MOD_ANG 1

# define COL_GREY_L 0x8A8A8A
# define COL_GREY_D 0x6F6F6F
# define COL_WHITE 0xFFFFFF

# define EPSILON 1e-6

// miniRT Functions
void	free_data(t_data *data);
t_data	*init_data(void);
int		check_main_args(int argc, char **argv);
int		generate_rays(t_data *data);
void	set_pixel_color(t_data *data, int x, int y, int color);
t_color	trace_ray(t_ray ray, t_data *data, int depth);
int		intersect_cylinder(t_ray ray, t_cylinder *cylinder,
			t_int *intersection);
float	check_body(t_ray ray, t_cylinder *cylinder,
			t_coeff coeffs, float discriminant);
int		intersect_plane(t_ray ray, t_plane *plane, t_int *intersection);
int		find_closest_int(t_ray ray, t_object *objects, t_int *closest_int);

// Shader
t_color	calculate_shading(t_int *intersection, t_data *data,
			t_v3 camera_position, double specular_exponent);
t_color	calculate_background_color(t_amb amb_light);
t_color	normalize_color(t_color color);
t_color	get_object_color(t_int *intersection);
int		is_point_in_shadow(t_v3 point, t_v3 light_dir,
			double light_dist, t_data *data);
t_color	calculate_diffuse_color(t_color dc, t_light *light,
			t_color obj, double di);

// Intersection Functions
void	update_intersection(t_int *intersection,
			t_ray ray, float t, t_v3 *center);
int		intersect_sphere(t_ray ray, t_sphere *sphere, t_int *intersection);
int		intersect(t_ray ray, void *object, t_type type, t_int *intersection);

// Mlx Functions
int		quit(t_data *data);
void	init_gui_window(t_data *data, t_mlx *m, int x, int y);
void	init_window(t_data *data);
void	start_loop(t_data *data);

// Utility Functions
int		ft_isspace(char c);
float	ft_atof(const char *s);
char	*ft_ftoa(float f);
int		cut_values_int(int *a, int max_a, int min_a);
float	cut_values(float *a, float max_a, float min_a);
void	free_camera_basis(t_data *data);
// Object transform
void	rotate_camera_x(t_camera *camera, double angle_deg);
void	rotate_camera_y(t_camera *camera, double angle_deg);
void	rotate_camera_z(t_camera *camera, double angle_deg);
void	rotate_plane_x(t_plane *pl, double ang_deg);
void	rotate_plane_y(t_plane *pl, double ang_deg);
void	rotate_plane_z(t_plane *pl, double ang_deg);
void	rotate_cylinder_x(t_cylinder *cy, double ang_deg);
void	rotate_cylinder_y(t_cylinder *cy, double ang_deg);
void	rotate_cylinder_z(t_cylinder *cy, double ang_deg);

// User input handling
int		handle_mouse(int button, int x, int y, t_data *data);
int		handle_mouse_gui(int button, int x, int y, t_data *data);
int		handle_keypress(int key, t_data *data);
void	move_camera_w_arrows(int key, t_data *data);

#endif
