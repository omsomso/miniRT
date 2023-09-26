/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:28:11 by kpawlows          #+#    #+#             */
/*   Updated: 2023/09/26 16:09:53 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "minirt.h"

typedef struct s_gui	t_gui;

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
	t_v3		*normal;
	t_color		color;
	t_pos		pl_ang_offset;
}				t_plane;

typedef struct s_cylinder
{
	t_v3		*center;
	t_v3		*normal;
	float		diameter;
	float		radius;
	float		height;
	t_color		color;
	t_pos		cy_ang_offset;
	float		cap_offsets[2];
}				t_cylinder;

typedef struct s_coeffs
{
	float	a;
	float	b;
	float	c;
}			t_coeff;

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
}				t_object;

// Intersection type
typedef struct s_intersection
{
	t_v3		point;
	t_v3		normal;
	t_object	*object;
	double		t;
}				t_int;

typedef struct s_amb
{
	float	ratio;
	t_color	color;
}			t_amb;

typedef struct s_camera
{
	t_v3	*pos;
	t_v3	*normal;
	t_v3	*up;
	t_v3	*right;
	int		fov;
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
	t_data		*data;
	t_pos		cam_ang_offset;
	int			sel_bckg;
	int			sel_par;
	int			obj_count;
}		t_gui;

typedef struct s_cy_params
{
	t_ray		ray;
	t_cylinder	*cylinder;
	float		t_body;
	float		t_caps;
	t_int		*intersection;
	float		oc_dot_n;
	t_v3		oc;
	float		dir_dot_n;
}				t_cy_params;

#endif
