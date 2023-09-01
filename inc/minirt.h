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

# define WIN_HEIGHT 480
# define WIN_WIDTH 640
# define MAX_RECURSION_DEPTH 3
# define NUM_SAMPLES 2


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

// Math Functions
t_v3	add_vectors(t_v3 a, t_v3 b);
t_v3	subtract_vectors(t_v3 a, t_v3 b);
t_v3	multiply_vector_scalar(t_v3 a, double s);
t_v3	normalize(t_v3	a);
float	distance_to_point(t_v3 a, t_v3 b);
float	vector_length(t_v3	a);
t_v3	cross_product(t_v3 a, t_v3 b);
float	dot_product(t_v3 a, t_v3 b);
float	deg_to_rad(float deg);
t_v3	new_v3(float x, float y, float z);
int		v3_equal(t_v3 v1, t_v3 v2);
t_v3	get_orthogonal(t_v3 v);
t_v3	multiply_matrix_vector(const t_matrix4 matrix, const t_v3 vector);
t_v3	calculate_sphere_normal(t_v3 sphere_center, t_v3 point_on_surface);

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
