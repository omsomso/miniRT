#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include "../mlx/mlx.h"

# define WIN_HEIGHT 480
# define WIN_WIDTH 640

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

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
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
	struct s_object	*next;
}				t_object;

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
	t_amb		*ambient_light;
	t_camera	*camera;
	t_light		*light;
	t_object	*objects;
	t_v3		***rays;
	int			win_width;
	int			win_height;
}				t_data;

int		parser(char *filename, t_object **objects, t_data *data);
void	free_data(t_data *data);


// Utils
int		ft_isspace(char c);
float	ft_atof(const char *s);

#endif