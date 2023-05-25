#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include "../mlx/mlx.h"

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

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}			t_mlx;

typedef struct  s_camera
{
	float	x;
	float	y;
	float	z;
	float	norm_x;
	float	norm_y;
	float	norm_z;
	int		fov;
}			t_camera;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct  s_light
{
	float	x;
	float	y;
	float	z;
	float	brightness;
	t_color	color;
}			t_light;

typedef struct	s_sphere
{
	float		x;
	float		y;
	float		z;
	float		diameter;
	t_color		color;
}				t_sphere;

typedef struct  s_plane
{
	float		x;
	float		y;
	float		z;
	float		norm_x;
	float		norm_y;
	float		norm_z;
	t_color		color;
}				t_plane;

typedef struct  s_cylinder
{
	float		x;
	float		y;
	float		z;
	float		norm_x;
	float		norm_y;
	float		norm_z;
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

typedef struct  s_object
{
	void		*object;
	t_type		type;
}				t_object;

typedef struct s_data
{
	t_mlx		*mlx;
	t_camera	*cameras;
	t_object	*objects;
	t_light		*lights;
	int			win_width;
	int			win_height;
}				t_data;

int	parser(char *filename, t_object *objects);

#endif