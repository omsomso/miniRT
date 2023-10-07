/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:52:17 by fcullen           #+#    #+#             */
/*   Updated: 2023/10/07 14:09:20 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_ray	offset_ray(t_data *data, t_ray ray, double dx, double dy)
{
	t_ray	offset_ray;
	t_v3	right_offset;
	t_v3	up_offset;
	t_v3	new_direction;

	offset_ray.origin = ray.origin;
	right_offset = mvs(*data->camera->right, dx);
	up_offset = mvs(*data->camera->up, dy);
	new_direction = add_v(ray.direction, right_offset);
	new_direction = add_v(new_direction, up_offset);
	offset_ray.direction = normalize(new_direction);
	return (offset_ray);
}

t_color	trace_ray(t_ray ray, t_data *data, int depth)
{
	t_int		intersection;
	t_color		pixel_color;

	(void) depth;
	if (find_closest_int(ray, data->objects, &intersection))
	{
		pixel_color = calculate_shading(&intersection, data,
				*data->camera->pos, 50);
	}
	else
		pixel_color = calculate_background_color(*data->ambient_light);
	return (pixel_color);
}

int	compute_camera_basis(t_camera *camera)
{
	t_v3	forward;
	t_v3	default_up;

	forward = normalize(*camera->normal);
	default_up.x = 0;
	default_up.y = 1;
	default_up.z = 0;
	camera->up = malloc(sizeof(t_v3));
	camera->right = malloc(sizeof(t_v3));
	if (!camera->up || !camera->right)
		return (1);
	if (fabs(dot_p(forward, default_up)) > 0.99)
		*camera->up = (t_v3){0, 0, 1};
	else
		*camera->up = default_up;
	*camera->right = cross_product(*camera->up, forward);
	*camera->up = cross_product(forward, *camera->right);
	return (0);
}

t_v3	calculate_pixel_relative_to_camera(int x, int y, const t_data *data)
{
	t_v3	*right;
	t_v3	*up;
	t_v3	*forward;
	double	ndc_x;
	double	ndc_y;

	right = data->camera->right;
	up = data->camera->up;
	forward = data->camera->normal;
	ndc_x = (2.0 * (x + 0.5) / data->win_width - 1.0)
		* data->aspect_ratio * data->fov_tan;
	ndc_y = (1.0 - 2.0 * (y + 0.5) / data->win_height)
		* data->fov_tan;
	return ((t_v3){
		ndc_x * right->x + ndc_y * up->x + forward->x,
		ndc_x * right->y + ndc_y * up->y + forward->y,
		ndc_x * right->z + ndc_y * up->z + forward->z
	});
}

// Generate rays for every pixel
// Create the ray and trace it
// Set the color of the pixel on the screen
// Display the rendered image
int	generate_rays(t_data *data)
{
	t_ray	ray ;
	int		x;
	int		y;

	compute_camera_basis(data->camera);
	data->aspect_ratio = (double)data->win_width / (double)data->win_height;
	data->fov_tan = tan(deg_to_rad(data->camera->fov * 0.5));
	y = -1;
	while (++y < data->win_height)
	{
		x = -1;
		while (++x < data->win_width)
		{
			ray.direction = normalize(
					calculate_pixel_relative_to_camera(x, y, data));
			ray.origin = *data->camera->pos;
			set_pixel_color(data, x, y, convert_tcolor_to_int(
					trace_ray(ray, data, MAX_RECURSION_DEPTH)));
		}
	}
	mlx_put_image_to_window(data->mlx->ptr,
		data->mlx->win, data->mlxdata->img, 0, 0);
	return (0);
}
