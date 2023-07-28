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
# define MAX_RECURSION_DEPTH 4

# define EVENT_KEYPRESS 2
# define EVENT_KEYRELEASE 3
# define EVENT_DESTROY 17

# define KEY_ESC 53
# define KEY_AR	124
# define KEY_AL	123
# define KEY_AU	126
# define KEY_AD	125
# define KEY_W	13
# define KEY_A	0
# define KEY_S	1
# define KEY_D	2

// Mlx Stuff
typedef struct s_mlx
{
	void	*ptr;
	void	*win;
}			t_mlx;

typedef struct s_mlxdata
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_mlxdata;

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

typedef struct	s_sphere
{
	t_v3		*center;
	float		diameter;
	t_color		color;
}				t_sphere;

typedef struct  s_plane
{
	t_v3		*point;
	t_v3		*normal_vec;
	t_color		color;
}				t_plane;

typedef struct  s_cylinder
{
	
	t_v3		*center;
	t_v3		*normal_vec;
	float		diameter;
	float		height;
	t_color		color;
}				t_cylinder;

typedef enum	e_type
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
	t_amb		*ambient_light;
	t_camera	*camera;
	t_light		*light;
	t_object	*objects;
	t_v3		***rays;
	int			win_width;
	int			win_height;
}				t_data;

// Ray Tracer Stuff
typedef struct	s_ray
{
	t_v3	origin;
	t_v3	direction;
}			t_ray;

typedef struct	s_matrix4
{
	double	m[4][4];
}			t_matrix4;

// miniRT Functions
int		parser(char *filename, t_object **objects, t_data *data);
void	free_data(t_data *data);
int		generate_rays(t_data *data);


// Utility Functions
int		ft_isspace(char c);
float	ft_atof(const char *s);

#endif