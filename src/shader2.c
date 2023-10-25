/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaphod <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:03:12 by zaphod           #+#    #+#             */
/*   Updated: 2023/09/26 16:04:51 by zaphod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Gets diffuse color
t_color	calculate_diffuse_color(t_color dc, t_light *light,
			t_color obj, double di)
{
	t_color		scaled_light_color;
	t_color		scaled_obj;
	t_color		diffuse_contribution;

	scaled_light_color.r = light->color.r / 255.0f;
	scaled_light_color.g = light->color.g / 255.0f;
	scaled_light_color.b = light->color.b / 255.0f;
	scaled_obj.r = obj.r / 255.0f;
	scaled_obj.g = obj.g / 255.0f;
	scaled_obj.b = obj.b / 255.0f;
	diffuse_contribution = mult_col(scaled_light_color, scaled_obj);
	diffuse_contribution = mult_cs(diffuse_contribution, di);
	diffuse_contribution = mult_cs(diffuse_contribution, light->brightness);
	diffuse_contribution.r *= 255.0f;
	diffuse_contribution.g *= 255.0f;
	diffuse_contribution.b *= 255.0f;
	return (add_colors(dc, diffuse_contribution));
}

// Gets background color
t_color	calculate_background_color(t_amb amb_light)
{
	t_color	bg_color;
	t_color	scaled_color;

	scaled_color.r = amb_light.color.r / 255.0f;
	scaled_color.g = amb_light.color.g / 255.0f;
	scaled_color.b = amb_light.color.b / 255.0f;
	bg_color = mult_cs(scaled_color, amb_light.ratio);
	bg_color.r = fmin(bg_color.r * 255.0f, 255.0f);
	bg_color.g = fmin(bg_color.g * 255.0f, 255.0f);
	bg_color.b = fmin(bg_color.b * 255.0f, 255.0f);
	return (bg_color);
}

// Checks if light is obstructed by another object
int	is_light_obstructed(t_ray shadow_ray, t_object *objects,
		double light_distance, t_int *intersection)
{
	t_int	closest_int;

	while (objects != NULL)
	{
		if (intersect(shadow_ray, objects->object, objects->type, &closest_int)
			&& closest_int.t < light_distance && closest_int.t > 0)
		{
			*intersection = closest_int;
			return (1);
		}
		objects = objects->next;
	}
	return (0);
}

// Checks if point is in shadow cast by another object
int	is_point_in_shadow(t_v3 point, t_v3 light_dir,
		double light_dist, t_data *data)
{
	t_ray		shadow_ray;
	t_int		intersection;
	t_v3		epsilon_offset;

	light_dir = mvs(light_dir, -1);
	epsilon_offset = mvs(light_dir, 0.001);
	shadow_ray.origin = add_v(point, epsilon_offset);
	shadow_ray.direction = normalize(light_dir);
	if (is_light_obstructed(shadow_ray, data->objects,
			light_dist, &intersection))
		return (1);
	else
		return (0);
}
