/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:52:17 by fcullen           #+#    #+#             */
/*   Updated: 2023/08/10 12:59:12 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void print_color(t_color color)
{
	printf("Color: R=%f, G=%f, B=%f\n", color.r, color.g, color.b);
}

void print_v(t_v3 p)
{
	printf("Point: x=%f, y=%f, z=%f\n", p.x, p.y, p.z);
}

void print_m(t_matrix4 matrix)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%f ", matrix.m[i][j]);
		}
		printf("\n");
	}
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

int intersect_plane(t_ray ray, t_plane *plane, t_intersection *intersection)
{
	float denominator = dot_product(ray.direction, *(plane->normal_vec));

	if (fabs(denominator) > 0.0001f) 
	{
		t_v3 oc = subtract_vectors(ray.origin, *(plane->point));
		float t = dot_product(oc, *(plane->normal_vec)) / denominator;
		if (t >= 0.0f)
		{
			intersection->point = add_vectors(ray.origin, multiply_vector_scalar(ray.direction, t));
			intersection->normal = multiply_vector_scalar(*(plane->normal_vec), -1);
			intersection->t = t;
			return 1;
		}
	}
	return 0;
}

int intersect_sphere(t_ray ray, t_sphere *sphere, t_intersection *intersection)
{
	t_v3 oc = subtract_vectors(*(sphere->center), ray.origin);
	float a = dot_product(ray.direction, ray.direction); // a is 1 for normalized vectors
	float b = 2.0 * dot_product(oc, ray.direction);
	float c = dot_product(oc, oc) - (sphere->radius * sphere->radius);
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return 0;
	else
	{
		float t1 = (-b - sqrt(discriminant)) / (2.0 * a);
		float t2 = (-b + sqrt(discriminant)) / (2.0 * a);

		float t;
		t = fmin(t1, t2);
		if (t < 0) // If the smallest t is negative, choose the other one.
			t = fmax(t1, t2);

		if (t < 0) // If both t values are negative, there's no valid intersection.
			return 0;

		intersection->point = add_vectors(ray.origin, multiply_vector_scalar(ray.direction, t));
		intersection->normal = normalize(subtract_vectors(intersection->point, *(sphere->center)));
		intersection->object = (t_object *)sphere;
		intersection->t = t;
		return 1;
	}
}


int intersect_cylinder(t_ray ray, t_cylinder *cylinder, t_intersection *intersection)
{
    t_v3 OC = subtract_vectors(*(cylinder->center), ray.origin);
    float dir_dot_norm = dot_product(ray.direction, *(cylinder->normal_vec));
    float OC_dot_norm = dot_product(OC, *(cylinder->normal_vec));

    // Compute the A, B, and C coefficients for the quadratic equation
    float A = dot_product(ray.direction, ray.direction) - dir_dot_norm * dir_dot_norm;
    float B = 2 * (dot_product(ray.direction, OC) - dir_dot_norm * OC_dot_norm);
    float C = dot_product(OC, OC) - OC_dot_norm * OC_dot_norm - cylinder->radius * cylinder->radius;

    float discriminant = B * B - 4 * A * C;

    float t_body = INFINITY; // Placeholder for the best intersection with the cylinder's body

    if (discriminant >= 0) 
    {
        float t_values[2] = {(-B - sqrt(discriminant)) / (2 * A), (-B + sqrt(discriminant)) / (2 * A)};
        int i = 0;
        while (i < 2)
        {
            float t = t_values[i];
            t_v3 P = add_vectors(ray.origin, multiply_vector_scalar(ray.direction, t));
            float y = dot_product(subtract_vectors(*(cylinder->center), P), *(cylinder->normal_vec));

            if (y > -cylinder->height/2 && y < cylinder->height/2 && t < t_body && t > 0)
            {
                t_body = t;
            }
            i++;
        }
    }

    // Check intersections with the cylinder's caps
    float t_caps = INFINITY; // Placeholder for the best intersection with the cylinder's caps
    float cap_offsets[2] = {-cylinder->height/2, cylinder->height/2};
    int j = 0;
    while (j < 2)
    {
        float cap_offset = cap_offsets[j];
        float t_cap = (cap_offset - OC_dot_norm) / dir_dot_norm;
        if(t_cap > 0)
        {
            t_v3 P = add_vectors(ray.origin, multiply_vector_scalar(ray.direction, t_cap));
            t_v3 to_center = subtract_vectors(*(cylinder->center), P);
            to_center = subtract_vectors(to_center, multiply_vector_scalar(*(cylinder->normal_vec), dot_product(to_center, *(cylinder->normal_vec))));

            if (dot_product(to_center, to_center) <= cylinder->radius * cylinder->radius && t_cap < t_caps)
            {
                t_caps = t_cap;
            }
        }
        j++;
    }

    // Determine the best intersection between the body and the caps
    if(t_body < INFINITY || t_caps < INFINITY)
    {
		float t_final;
		if (t_body < INFINITY && (t_body < t_caps || t_caps == INFINITY)) {
			t_final = t_body;
		} else if (t_caps < INFINITY) {
			t_final = t_caps;
		} else {
			return 0;  // No valid intersection
		}

        intersection->point = add_vectors(ray.origin, multiply_vector_scalar(ray.direction, t_final));
        if(t_final == t_body)
		{
		t_v3 vector_to_intersection = subtract_vectors(intersection->point, *(cylinder->center));
		t_v3 projected_vector = multiply_vector_scalar(*(cylinder->normal_vec), dot_product(vector_to_intersection, *(cylinder->normal_vec)));
		t_v3 normal = subtract_vectors(vector_to_intersection, projected_vector);
		intersection->normal = normalize(multiply_vector_scalar(normal, -1));

			// intersection->normal = normalize(normal);
		}
		else
		{
			intersection->normal = (t_final == t_caps && OC_dot_norm > 0) ? multiply_vector_scalar(*(cylinder->normal_vec), -1) :  *(cylinder->normal_vec);
		}

        intersection->t = t_final;
        return 1;
    }

    return 0;
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

int is_light_obstructed(t_ray shadow_ray, t_object *objects, double light_distance, t_intersection *intersection)
{
	t_intersection closest_intersection;

	while (objects != NULL)
	{
		if (intersect(shadow_ray, objects->object, objects->type, &closest_intersection) &&
			closest_intersection.t < light_distance && closest_intersection.t > 0)
		{
			// An object is obstructing the light, update the intersection variable
			*intersection = closest_intersection;
			return 1; // the light is obstructed
		}
		objects = objects->next;
	}
	return 0; // the light is not obstructed
}

int is_point_in_shadow(t_v3 point, t_v3 light_dir, double light_dist, t_data *data)
{
	t_ray shadow_ray;
	t_intersection intersection;

	// Create a shadow ray starting from the point and heading towards the light source
	light_dir = multiply_vector_scalar(light_dir, -1);
	t_v3 epsilon_offset = multiply_vector_scalar(light_dir, 0.0001);
	shadow_ray.origin = add_vectors(point, epsilon_offset);
	shadow_ray.direction = normalize(light_dir);

	// Check if the shadow ray intersects with any object before reaching the light source
	if (is_light_obstructed(shadow_ray, data->objects, light_dist, &intersection))
	{
		// The point is in shadow, return 1
		return 1;
	}
	else
	{
		// The point is not in shadow, return 0
		return 0;
	}
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
	return (diffuse_color);
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

	return (color);
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
	}
	else
		pixel_color = calculate_background_color(*data->ambient_light);
	pixel_color = normalize_color(pixel_color);  // Normalize color here
	return (pixel_color);
}

int generate_rays(t_data *data)
{
	// Compute camera's basis vectors
	t_v3 forward = normalize(*data->camera->normal_vec);
	t_v3 default_up = {0, 1, 0};
	t_v3 up;
	
	if (fabs(dot_product(forward, default_up)) > 0.99)
		up = (t_v3){0, 0, 1};
	else
		up = default_up;

	t_v3 right = cross_product(up, forward);
	up = cross_product(forward, right);

	// Prepare values for ray generation
	double aspect_ratio = (double)data->win_width / (double)data->win_height;
	double fov_tan = tan(deg_to_rad(data->camera->fov * 0.5));

	// Generate rays for every pixel
	for (int y = 0; y < data->win_height; y++)
	{
		for (int x = 0; x < data->win_width; x++)
		{
			double ndc_x = (2.0 * (x + 0.5) / data->win_width - 1.0) * aspect_ratio * fov_tan;
			double ndc_y = (1.0 - 2.0 * (y + 0.5) / data->win_height) * fov_tan;

			t_v3 pixel_relative_to_camera = {
				ndc_x * right.x + ndc_y * up.x + forward.x,
				ndc_x * right.y + ndc_y * up.y + forward.y,
				ndc_x * right.z + ndc_y * up.z + forward.z
			};
			
			t_v3 ray_direction = normalize(pixel_relative_to_camera);
			
			// Create the ray and trace it
			t_ray ray = { .origin = *data->camera->pos, .direction = ray_direction };
			t_color pixel_color = trace_ray(ray, data, MAX_RECURSION_DEPTH);
			// Set the color of the pixel on the screen
			set_pixel_color(data, x, y, convert_tcolor_to_int(pixel_color));
		}
	}
	// Display the rendered image
	mlx_put_image_to_window(data->mlx->ptr, data->mlx->win, data->mlxdata->img, 0, 0);
	return 0;
}

