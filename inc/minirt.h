#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include "../mlx/mlx.h"


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

# define MOD_POS 0.2
# define MOD_RADIUS 0.05
# define MOD_FOV 1

# define COL_GREY_L 0x8A8A8A
# define COL_GREY_D 0x6F6F6F
# define COL_WHITE 0xFFFFFF

#define EPSILON 1e-6


typedef struct s_gui t_gui;

// Mlx Stuff
typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	void	*win_gui;
}			t_mlx;

typedef struct s_mlxdata
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_mlxdata;

typedef struct s_pics
{
	void	*bckg;
	void	*sel;
	void	*sel_p;
	void	*empty;
}			t_pics;

// Parser Stuff
typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}			t_color;

typedef struct s_v3
{
	float	x;
	float	y;
	float	z;
}			t_v3;

typedef struct s_pos
{
	int	x;
	int	y;
	int	z;
}			t_pos;

typedef struct s_sphere
{
	t_v3		*center;
	float		diameter;
	float		radius;
	t_color		color;
}				t_sphere;

typedef struct s_plane
{
	t_v3		*point;
	t_v3		*normal_vec;
	t_color		color;
	t_pos		pl_ang_offset;
}				t_plane;

typedef struct s_cylinder
{
	t_v3		*center;
	t_v3		*normal_vec;
	float		diameter;
	float		radius;
	float		height;
	t_color		color;
	t_pos		cy_ang_offset;
}				t_cylinder;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}				t_type;

typedef struct s_object
{
	void			*object;
	t_type			type;
	double			ambient_coefficient;
	double			diffuse_coefficient;
	struct s_object	*next;
	double			distance;
	bool			check;
	bool			mirror;
}				t_object;

typedef struct s_intersection
{
	t_v3		point;      // Intersection point in 3D space
	t_v3		normal;     // Surface normal at the intersection point
	t_object	*object;      // Object that was intersected
	double		t;             // Parameter value along the ray where the intersection occurs
}				t_intersection;

typedef struct s_amb
{
	float	ratio;
	t_color	color;
}			t_amb;

typedef struct  s_camera
{
	t_v3	*pos;			//position
	t_v3	*normal_vec;	//orientation
	t_v3	*up;
	t_v3	*right;
	int		fov;			//field of view
}			t_camera;

typedef struct s_light
{
	t_v3	*pos;
	float	brightness;
	t_color	color;
}			t_light;

typedef struct s_data
{
	t_mlx		*mlx;
	t_mlxdata	*mlxdata;
	t_pics		*pics;
	t_amb		*ambient_light;
	t_camera	*camera;
	t_light		*light;
	t_object	*objects;
	t_v3		***rays;
	t_gui		*gui;
	int			auto_retrace;
	int			win_width;
	int			win_height;
	double		aspect_ratio;
	double		fov_tan;
}				t_data;

// Ray Tracer Stuff
typedef struct s_ray
{
	t_v3	origin;
	t_v3	direction;
}			t_ray;

typedef struct s_matrix4
{
	double	m[4][4];
}			t_matrix4;

typedef struct s_gui
{
	t_pos		mouse_pos;
	t_pos		draw_pos;
	t_object	*objects;
	t_mlx		*mlx;
	t_pics		*pics;
	t_data 		*data;
	t_pos		cam_ang_offset;
	int			sel_bckg;
	int			sel_par;
	int			obj_count;
}		t_gui;

#include "parser.h"

// miniRT Functions
void	free_data(t_data *data);
int		generate_rays(t_data *data);
void	set_pixel_color(t_data *data, int x, int y, int color);
t_color	trace_ray(t_ray ray, t_data *data, int depth);

// Utility Functions
int		ft_isspace(char c);
float	ft_atof(const char *s);
char	*ft_ftoa(float f);

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
bool	v3_equal(t_v3 v1, t_v3 v2);
t_v3	get_orthogonal(t_v3 v);
t_v3	multiply_matrix_vector(const t_matrix4 matrix, const t_v3 vector);
t_v3	calculate_sphere_normal(t_v3 sphere_center, t_v3 point_on_surface);

void 	rotate_camera_x(t_camera *camera, double angle_deg);
void	rotate_camera_y(t_camera *camera, double angle_deg);
void	rotate_camera_z(t_camera *camera, double angle_deg);

void	rotate_plane_x(t_plane *pl, double ang_deg);
void 	rotate_plane_y(t_plane *pl, double ang_deg);
void	rotate_plane_z(t_plane *pl, double ang_deg);

void	rotate_cylinder_x(t_cylinder *cy, double ang_deg);
void	rotate_cylinder_y(t_cylinder *cy, double ang_deg);
void	rotate_cylinder_z(t_cylinder *cy, double ang_deg);

int		handle_mouse_gui(int button, int x, int y, t_data *data);
int 	handle_mouse(int button, int x, int y, t_data *data);

t_gui	*init_gui_struct(t_data *data);
t_gui	*update_gui_struct(t_data *data, t_gui *gui, t_pos mouse_pos);
int		draw_gui(t_data *data, t_gui *gui);
void	conditional_retrace(t_data *data, int button);
int		count_objects(t_object *objects);
int		compute_gui_height(int obj_count);
int		compute_gui_width(int obj_count);

t_v3	get_pos_sphere(t_sphere *sphere);
t_v3	get_pos_plane(t_plane *plane);
t_v3	get_pos_cylinder(t_cylinder *cylinder);
t_v3	get_light_pos(t_light *light);
t_v3	get_camera_pos(t_camera *camera);
t_v3	get_rot_plane(t_plane *plane);
t_v3	get_rot_cylinder(t_cylinder *cylinder);

#endif