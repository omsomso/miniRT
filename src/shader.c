/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:49:50 by fcullen           #+#    #+#             */
/*   Updated: 2023/09/26 16:04:41 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Get diffuse color component
// Scale down colors to [0, 1]
// Check if the point is in shadow
// Calculate the diffuse color contribution
// Scale the diffuse contribution by light brightness
// Scale up colors to [0, 255]
// Add the diffuse contribution to the diffuse color
t_color	get_diff(t_int *intersection, t_light *light, t_data *data)
{
	t_color		diffuse_color;
	t_v3		light_dir;
	double		light_dist;
	double		diffuse_intensity;
	t_color		obj;

	diffuse_color = (t_color){0, 0, 0};
	light_dir = normalize(sub_v(*light->pos, intersection->point));
	light_dist = distance_to_point(*light->pos, intersection->point);
	diffuse_intensity = fmax(dot_p(intersection->normal, light_dir), 0.0);
	obj = get_object_color(intersection);
	if (!is_point_in_shadow(intersection->point, light_dir, light_dist, data))
		diffuse_color = calculate_diffuse_color(diffuse_color,
				light, obj, diffuse_intensity);
	return (diffuse_color);
}

// Get ambient color component
// Scale down colors to [0, 1]
// Calculate the ambient color contribution
// Scale up colors to [0, 255]
t_color	get_amb(t_int *intersection, t_data *data)
{
	t_color	amb;
	t_color	obj;
	t_color	scaled_obj;
	t_color	scaled_amb;

	obj = get_object_color(intersection);
	scaled_obj = (t_color){obj.r / 255.0f, obj.g / 255.0f, obj.b / 255.0f};
	scaled_amb = (t_color){data->ambient_light->color.r / 255.0f,
		data->ambient_light->color.g / 255.0f,
		data->ambient_light->color.b / 255.0f};
	amb = mult_col(scaled_obj, scaled_amb);
	amb = mult_cs(amb, data->ambient_light->ratio);
	amb.r *= 255.0f;
	amb.g *= 255.0f;
	amb.b *= 255.0f;
	return (amb);
}

// Gets reflection direction
t_v3	reflect(t_v3 incident_dir, t_v3 normal)
{
	double	dot_p_value;
	t_v3	reflection;

	dot_p_value = dot_p(incident_dir, normal);
	reflection = sub_v(mvs(normal, 2.0 * dot_p_value), incident_dir);
	return (normalize(reflection));
}

// Gets specular color component
t_color	get_spec(t_int *intersection, t_light *light,
			t_v3 camera_position, double specular_exponent)
{
	t_v3	light_dir;
	t_v3	reflect_dir;
	t_v3	view_dir;
	t_color	specular_color;
	double	specular_intensity;

	light_dir = normalize(sub_v(*light->pos, intersection->point));
	reflect_dir = normalize(reflect(mvs(light_dir, -1.0),
				intersection->normal));
	view_dir = normalize(sub_v(camera_position, intersection->point));
	specular_color = light->color;
	specular_intensity = pow(fmax(dot_p(view_dir, reflect_dir), 0.0),
			specular_exponent);
	specular_color = light->color;
	specular_color.r *= specular_intensity * light->brightness;
	specular_color.g *= specular_intensity * light->brightness;
	specular_color.b *= specular_intensity * light->brightness;
	return (specular_color);
}

// Calculate shading combining ambient, diffuse and specular components,
// while ensuring color components are within [0, 255]
t_color	calculate_shading(t_int *intersection, t_data *data,
			t_v3 camera_position, double specular_exponent)
{
	t_color	amb;
	t_color	diffuse_color;
	t_color	specular_color;
	t_color	total_color;

	amb = get_amb(intersection, data);
	diffuse_color = get_diff(intersection, data->light, data);
	specular_color = get_spec(intersection, data->light,
			camera_position, specular_exponent);
	total_color = add_colors(add_colors(amb, diffuse_color), specular_color);
	total_color.r = fmin(fmax(total_color.r, 0.0), 255.0);
	total_color.g = fmin(fmax(total_color.g, 0.0), 255.0);
	total_color.b = fmin(fmax(total_color.b, 0.0), 255.0);
	return (total_color);
}
