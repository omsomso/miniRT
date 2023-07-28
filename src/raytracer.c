/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:52:17 by fcullen           #+#    #+#             */
/*   Updated: 2023/07/28 15:46:42 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

float	deg_to_rad(float deg)
{
	return ((deg * M_PI) / 180);
}

t_v3 add_vectors(t_v3 a, t_v3 b)
{
	t_v3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_v3 subtract_vectors(t_v3 a, t_v3 b)
{
	t_v3	result;

	result.x = b.x - a.x;
	result.y = b.y - a.y;
	result.z = b.z - a.z;
	return (result);
}

t_v3 multiply_vector_scalar(t_v3 a, double s)
{
	t_v3 result;
	result.x = a.x * s;
	result.y = a.y * s;
	result.z = a.z * s;
	return (result);
}

t_v3	normalize(t_v3	a)
{
	double	length;

	length = sqrt(a.x * a.x + a.y
			* a.y + a.z * a.z);
	if (length != 0.0)
	{
		a.x /= length;
		a.y /= length;
		a.z /= length;
	}
	return (a);
}

float	distance_to_point(t_v3 a, t_v3 b)
{
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	float dz = b.z - a.z;
	return (sqrt(dx * dx + dy * dy + dz * dz));
}

float	vector_length(t_v3	a)
{
	float	length;

	length = sqrt(a.x * a.x + a.y
			* a.y + a.z * a.z);
	return (length);
}

t_v3	cross_product(t_v3 a, t_v3 b)
{
	t_v3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

float	dot_product(t_v3 a, t_v3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_color add_colors(t_color color1, t_color color2)
{
	t_color result;
	result.r = color1.r + color2.r;
	result.g = color1.g + color2.g;
	result.b = color1.b + color2.b;
	return (result);
}

t_color multiply_colors(t_color color1, t_color color2)
{
	t_color result;
	result.r = color1.r * color2.r;
	result.g = color1.g * color2.g;
	result.b = color1.b * color2.b;
	return (result);
}

t_color multiply_color_scalar(t_color color, float s)
{
	t_color result;
	result.r = color.r * s;
	result.g = color.g * s;
	result.b = color.b * s;
	return (result);
}

t_matrix4 camera_to_world_matrix(t_camera *camera)
{
	t_v3 forward = normalize(*camera->normal_vec);
	t_v3 up = (t_v3){0, 1, 0};
	if (fabsf(dot_product(forward, up)) > 0.999)
	{
		up = (t_v3){1, 0, 0};
	}
	t_v3 right = normalize(cross_product(up, forward));
	up = cross_product(forward, right);

	t_matrix4 cam_to_world = {{
		{right.x, right.y, right.z, 0.0},
		{up.x, up.y, up.z, 0.0},
		{-forward.x, -forward.y, -forward.z, 0.0},
		{camera->pos->x, camera->pos->y, camera->pos->z, 1.0},
	}};

	return (cam_to_world);
}

t_v3 multiply_matrix_vector(const t_matrix4 matrix, const t_v3 vector)
{
	t_v3 result;

	result.x = matrix.m[0][0] * vector.x + matrix.m[0][1] * vector.y + matrix.m[0][2] * vector.z;
	result.y = matrix.m[1][0] * vector.x + matrix.m[1][1] * vector.y + matrix.m[1][2] * vector.z;
	result.z = matrix.m[2][0] * vector.x + matrix.m[2][1] * vector.y + matrix.m[2][2] * vector.z;
	
	return result;
}


t_v3	calculate_sphere_normal(t_v3 sphere_center, t_v3 point_on_surface)
{
	t_v3 surface_to_center = subtract_vectors(sphere_center, point_on_surface);
	t_v3 normal_vector = normalize(surface_to_center);
	return (normal_vector);
}

int intersect_plane(t_ray ray, t_plane *plane, t_intersection *intersection)
{
	float denominator = dot_product(ray.direction, *(plane->normal_vec));

	if (fabs(denominator) > 0.0001f) 
	{
		t_v3 oc = subtract_vectors(ray.origin, *(plane->point));
		float t = -dot_product(oc, *(plane->normal_vec)) / denominator;
		if (t >= 0.0f)
		{
			intersection->point = add_vectors(ray.origin, multiply_vector_scalar(ray.direction, t));
			intersection->normal = normalize(*(plane->normal_vec));
			intersection->t = t;
			return 1;
		}
	}
	return 0;
}

int intersect_cylinder(t_ray ray, t_cylinder *cylinder, t_intersection *intersection)
{
	t_v3 oc = subtract_vectors(ray.origin, *(cylinder->center));
	t_v3 dir = ray.direction;
	dir.y = 0;
	oc.y = 0;

	float a = dot_product(dir, dir);
	float b = 2.0 * dot_product(oc, dir);
	float c = dot_product(oc, oc) - cylinder->diameter * cylinder->diameter;
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
	{
		return 0;
	}
	else
	{
		float t = (-b - sqrt(discriminant)) / (2.0 * a);
		intersection->point = add_vectors(ray.origin, multiply_vector_scalar(ray.direction, t));
		intersection->normal = normalize(subtract_vectors(intersection->point, *(cylinder->center)));
		intersection->t = t;
		return 1;
	}
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

int convert_tcolor_to_int(t_color color)
{
	int intcolor;

	intcolor = 0;
	// Bit shifting and bitwise OR operations to combine the RGB components
	intcolor |= ((int)(color.r) & 0xFF) << 16;
	intcolor |= ((int)(color.g) & 0xFF) << 8;
	intcolor |= ((int)(color.b) & 0xFF);

	return (intcolor);
}

void print_color(t_color color)
{
	printf("Color: R=%f, G=%f, B=%f\n", color.r, color.g, color.b);
}

void print_point(t_v3 p)
{
	printf("Point: x=%f, y=%f, z=%f\n", p.x, p.y, p.z);
}

bool is_vector_normalized(t_v3 vector)
{
	double length = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	const double epsilon = 1e-6; // A small value for comparing doubles

	printf("%d\n", fabs(length - 1.0) < epsilon);
	return fabs(length - 1.0) < epsilon;
}

t_color visualize_normals(t_intersection *intersection)
{
	t_color color;

	// Normalize the normal vector to ensure it has unit length
	t_v3 normal = normalize(intersection->normal);

	// Map the x, y, and z components of the normal to the RGB values
	color.r = (unsigned char)((normal.x + 1.0) * 127.5);
	color.g = (unsigned char)((normal.y + 1.0) * 127.5);
	color.b = (unsigned char)((normal.z + 1.0) * 127.5);

	return color;
}

t_color calculate_background_color(t_amb ambient_light)
{
	t_color background_color;

	background_color = multiply_color_scalar(ambient_light.color, ambient_light.ratio);
	return (background_color);
}

t_color normalize_color(t_color color)
{
	color.r = fmin(fmax(color.r, 0), 255);
	color.g = fmin(fmax(color.g, 0), 255);
	color.b = fmin(fmax(color.b, 0), 255);

	return color;
}

t_color get_object_color(t_intersection *intersection)
{
	t_color object_color = {0, 0, 0};

	if (intersection->object->type == SPHERE)
		object_color = ((t_sphere *)intersection->object->object)->color;
	else if (intersection->object->type == PLANE)
		object_color = ((t_plane *)intersection->object->object)->color;
	else if (intersection->object->type == CYLINDER)
		object_color = ((t_cylinder *)intersection->object->object)->color;

	return object_color;
}

int intersect_sphere(t_ray ray, t_sphere *sphere, t_intersection *intersection)
{
	t_v3 oc = subtract_vectors(*(sphere->center), ray.origin);
	float a = dot_product(ray.direction, ray.direction);
	float b = 2.0 * dot_product(oc, ray.direction);
	float c = dot_product(oc, oc) - ((sphere->diameter / 2) * (sphere->diameter / 2));
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
	{
		return 0;
	}
	else
	{
		float t = (-b - sqrt(discriminant)) / (2.0 * a);
		intersection->point = add_vectors(ray.origin, multiply_vector_scalar(ray.direction, t));

		// Calculate the normal vector at the intersection point
		t_v3 intersection_to_center = subtract_vectors(intersection->point, *(sphere->center));
		intersection->normal = normalize(intersection_to_center);

		intersection->t = t;
		return 1;
	}
}

int intersect(t_ray ray, void *object, t_type type, t_intersection *intersection)
{
	if (type == SPHERE)
		return intersect_sphere(ray, (t_sphere *)object, intersection);
	else if (type == PLANE)
		return intersect_plane(ray, (t_plane *)object, intersection);
	else if (type == CYLINDER)
		return intersect_cylinder(ray, (t_cylinder *)object, intersection);
	else
		return 0;
}

int	find_closest_intersection(t_ray ray, t_object *objects, t_intersection *closest_intersection)
{
	t_intersection	intersection;
	int				found_intersection = 0;
	double			closest_t = INFINITY;

	while (objects != NULL)
	{
		if (intersect(ray, objects->object, objects->type, &intersection) && intersection.t < closest_t)
		{
			*closest_intersection = intersection;
			closest_intersection->object = objects;
			closest_t = intersection.t;
			found_intersection = 1;
		}
		objects = objects->next;
	}
	return (found_intersection);
}

int	is_point_in_shadow(t_v3 point, t_v3 light_dir, double light_dist, t_data *data)
{
	t_ray			shadow_ray;
	t_intersection	intersection;

	// Create a shadow ray starting from the point and heading towards the light source
	t_v3 epsilon_offset = multiply_vector_scalar(light_dir, 0.0001);
	shadow_ray.origin = subtract_vectors(point, epsilon_offset);
	shadow_ray.direction = light_dir;

	// Check if the shadow ray intersects with any object before reaching the light source
	if (find_closest_intersection(shadow_ray, data->objects, &intersection) &&
		intersection.t < light_dist)
		return (1);
	else
		return (0);
}

t_color calculate_diffuse_color(t_intersection *intersection, t_light *light, t_data *data)
{
	t_color diffuse_color = {0, 0, 0};
	t_v3 light_dir = normalize(subtract_vectors(*light->pos, intersection->point));
	double light_dist = distance_to_point(*light->pos, intersection->point);
	double diffuse_intensity = fmax(dot_product(intersection->normal, light_dir), 0.0);

	t_color light_color = light->color;
	t_color object_color = get_object_color(intersection);

	// Scale down colors to [0, 1]
	t_color scaled_light_color = {light_color.r / 255.0f, light_color.g / 255.0f, light_color.b / 255.0f};
	t_color scaled_object_color = {object_color.r / 255.0f, object_color.g / 255.0f, object_color.b / 255.0f};

	// Check if the point is in shadow
	if (!is_point_in_shadow(intersection->point, light_dir, light_dist, data))
	{
		// Calculate the diffuse color contribution
		t_color diffuse_contribution = multiply_colors(scaled_light_color, scaled_object_color);
		diffuse_contribution = multiply_color_scalar(diffuse_contribution, diffuse_intensity);


		// Scale the diffuse contribution by light brightness
		diffuse_contribution = multiply_color_scalar(diffuse_contribution, light->brightness);

		// Scale up colors to [0, 255]
		diffuse_contribution.r *= 255.0f;
		diffuse_contribution.g *= 255.0f;
		diffuse_contribution.b *= 255.0f;

		// Add the diffuse contribution to the diffuse color
		diffuse_color = add_colors(diffuse_color, diffuse_contribution);

	}

	return diffuse_color;
}

t_color calculate_ambient_color(t_intersection *intersection, t_data *data)
{
	t_color ambient_color;
	t_color object_color = get_object_color(intersection);

	// Scale down colors to [0, 1]
	t_color scaled_object_color = {object_color.r / 255.0f, object_color.g / 255.0f, object_color.b / 255.0f};
	t_color scaled_ambient_light_color = {data->ambient_light->color.r / 255.0f, data->ambient_light->color.g / 255.0f, data->ambient_light->color.b / 255.0f};

	// Calculate the ambient color contribution
	ambient_color = multiply_colors(scaled_object_color, scaled_ambient_light_color);
	ambient_color = multiply_color_scalar(ambient_color, data->ambient_light->ratio);

	// Scale up colors to [0, 255]
	ambient_color.r *= 255.0f;
	ambient_color.g *= 255.0f;
	ambient_color.b *= 255.0f;

	return ambient_color;
}



t_color calculate_shading(t_intersection *intersection, t_data *data)
{
	t_color color = {0, 0, 0};
	t_light *light = data->light;

	t_color ambient_color = calculate_ambient_color(intersection, data);
	t_color diffuse_color = calculate_diffuse_color(intersection, light, data);

	color = add_colors(ambient_color, diffuse_color);

	return color;
}


t_color trace_ray(t_ray ray, t_data *data, int depth)
{
	t_intersection intersection;
	t_color pixel_color;
	(void)depth;

	if (find_closest_intersection(ray, data->objects, &intersection))
	{
		// Calculate shading and lighting at the intersection point
		pixel_color = calculate_shading(&intersection, data);
		// pixel_color = visualize_normals(&intersection);
	}
	else
		pixel_color = calculate_background_color(*data->ambient_light);

	pixel_color = normalize_color(pixel_color);  // Normalize color here

	return pixel_color;
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

	y = 0;
	fov_tan = tan(deg_to_rad(data->camera->fov * 0.5));
	aspect_ratio = (double)data->win_width / (double)data->win_height;
	cam_to_world = camera_to_world_matrix(data->camera);
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			ndc_x = ((x + 0.5) / data->win_width) * 2.0 - 1.0;
			ndc_x *= aspect_ratio * fov_tan;

			ndc_y = 1.0 - ((y + 0.5) / data->win_height) * 2.0;
			ndc_y *= fov_tan;

			ray_direction.x = ndc_x;
			ray_direction.y = ndc_y;
			ray_direction.z = 1.0;
			ray_direction = multiply_matrix_vector(cam_to_world, ray_direction);
			ray.origin = *data->camera->pos;
			ray.direction = normalize(ray_direction);
			pixel_color = trace_ray(ray, data, 3);
			set_pixel_color(data, x, y, convert_tcolor_to_int(pixel_color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx->ptr,
		data->mlx->win, data->mlxdata->img, 0, 0);
	return (0);
}
