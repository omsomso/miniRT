/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaphod <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:01:11 by zaphod           #+#    #+#             */
/*   Updated: 2023/09/26 15:33:56 by zaphod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Normalizes color
t_color	normalize_color(t_color color)
{
	color.r = fmin(fmax(color.r, 0), 255);
	color.g = fmin(fmax(color.g, 0), 255);
	color.b = fmin(fmax(color.b, 0), 255);
	return (color);
}

// Gets object color
t_color	get_object_color(t_int *intersection)
{
	t_color	object_color;

	object_color = (t_color){0, 0, 0};
	if (intersection->object->type == SPHERE)
		object_color = ((t_sphere *)intersection->object->object)->color;
	else if (intersection->object->type == PLANE)
		object_color = ((t_plane *)intersection->object->object)->color;
	else if (intersection->object->type == CYLINDER)
		object_color = ((t_cylinder *)intersection->object->object)->color;
	return (object_color);
}
