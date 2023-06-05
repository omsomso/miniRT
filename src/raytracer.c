/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:52:17 by fcullen           #+#    #+#             */
/*   Updated: 2023/06/05 18:55:35 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Mlx Functions
// Initialise necessary mlx values
void	mlxdata_init(t_data *data)
{
	t_mlxdata	*mlxdata;

	data->mlx->ptr = mlx_init();
	data->mlx->win = mlx_new_window(data->mlx->ptr, 1080, 720, "data");
	data->mlxdata = malloc(sizeof(*mlxdata));
	if (!data->mlxdata)
		return ;
	data->mlxdata->img = mlx_new_image(data->mlx->ptr, 1080, 720);
	data->mlxdata->addr = mlx_get_data_addr(data->mlxdata->img,
			&data->mlxdata->bits_per_pixel, &data->mlxdata->line_length,
			&data->mlxdata->endian);
}

/*
Ray Generation
1. Calculate the aspect ratio of the image by dividing the width by the height.

2. Calculate the tangent of half the FOV in radians. This value will be used to convert pixel coordinates to normalized device coordinates.

3. Iterate over each pixel in the image, from (0,0) to (width-1,height-1).

4. For each pixel, convert the pixel coordinates to normalized device coordinates (NDC). NDC range from -1 to 1 in both the x and y directions.

5. Then transform the NDC coordinates to camera space. This step maps the NDC coordinates to the camera's viewing plane.

6. Next, transform the ray direction from camera space to world space. This transformation takes into account the camera's position and orientation in the scene.

7. Create a ray with its origin at the camera position and its direction as the normalized ray direction.

8. Finally, trace the ray by calling the trace_ray function, passing the ray, the scene objects, and lights.
The trace_ray function will handle the intersection calculations, shading, reflections, and refractions, and return the pixel color.

9. Set the pixel color in the image buffer using the set_pixel_color function.
*/

float	deg_to_rad(float deg)
{
	return ((deg * M_PI) / 180);
}

t_v3	normalize(t_v3	vector)
{
	double	length;

	length = sqrt(vector.x * vector.x + vector.y
			* vector.y + vector.z * vector.z);
	if (length != 0.0)
	{
		vector.x /= length;
		vector.y /= length;
		vector.z /= length;
	}
	return (vector);
}

t_v3	cross_product(t_v3 a, t_v3 b)
{
	t_v3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_matrix4	camera_to_world_matrix(t_camera camera)
{
	t_v3 up;
	t_v3 right;
	t_v3 forward;
	t_matrix4 cam_to_world;

	forward = normalize(camera.normal_vec);
	right = cross_product((t_v3){0, 1, 0}, forward);
	up = cross_product(forward, right);

	cam_to_world.m[0][0] = right.x;
	cam_to_world.m[0][1] = right.y;
	cam_to_world.m[0][2] = right.z;
	cam_to_world.m[0][3] = 0.0;

	cam_to_world.m[1][0] = up.x;
	cam_to_world.m[1][1] = up.y;
	cam_to_world.m[1][2] = up.z;
	cam_to_world.m[1][3] = 0.0;

	cam_to_world.m[2][0] = -forward.x;
	cam_to_world.m[2][1] = -forward.y;
	cam_to_world.m[2][2] = -forward.z;
	cam_to_world.m[2][3] = 0.0;

	cam_to_world.m[3][0] = camera.pos.x;
	cam_to_world.m[3][1] = camera.pos.y;
	cam_to_world.m[3][2] = camera.pos.z;
	cam_to_world.m[3][3] = 1.0;

	return (cam_to_world);
}

t_v3	multiply_matrix_vector(const t_matrix4 matrix, const t_v3 vector)
{
	t_v3 result;

	result.x = matrix.m[0][0] * vector.x + matrix.m[0][1] * vector.y + matrix.m[0][2] * vector.z + matrix.m[0][3];
	result.y = matrix.m[1][0] * vector.x + matrix.m[1][1] * vector.y + matrix.m[1][2] * vector.z + matrix.m[1][3];
	result.z = matrix.m[2][0] * vector.x + matrix.m[2][1] * vector.y + matrix.m[2][2] * vector.z + matrix.m[2][3];

	return (result);
}

void	set_pixel_color(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= data->win_width
		|| y < 0 || y >= data->win_height)
		return ;
	dst = data->mlxdata->addr + (y * data->mlxdata->line_length
			+ x * (data->mlxdata->bits_per_pixel / 8));
	*(unsigned int *) dst = color ;
}

int	generate_rays(t_data *data)
{
	int			x;
	int			y;
	double		ndc_x;
	double		ndc_y;
	double		fov_tan;
	double		aspect_ratio;
	t_matrix4	cam_to_world;
	t_v3		ray_direction;
	t_ray		ray;
	t_color		pixel_color;

	x = 0;
	y = 0;
	fov_tan = tan(deg_to_rad(data->camera->fov * 0.5));
	aspect_ratio = (double)data->win_width / (double)data->win_height;
	while (y++ < data->win_height)
	{
		while (x++ < data->win_width)
		{
			ndc_x = (2.0 * ((x + 0.5) / data->win_width) - 1.0)
				* aspect_ratio * fov_tan;
			ndc_y = (-1.0 * ((y +0.5) / data->win_height)) * fov_tan;
			ray_direction = normalize((t_v3){ndc_x, ndc_y, 1.0});
			cam_to_world = camera_to_world_matrix(*(data->camera));
			ray_direction = multiply_matrix_vector(cam_to_world, ray_direction);
			ray.origin = data->camera->pos;
			ray.direction = normalize(ray_direction);
			pixel_color = trace_ray(ray, data->objects, data->light, 0);
			set_pixel_color(data, x, y, pixel_color);
		}
	}
}
