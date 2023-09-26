/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:39:07 by fcullen           #+#    #+#             */
/*   Updated: 2023/09/26 15:40:21 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Finds closest intersection
int	find_closest_int(t_ray ray, t_object *objects, t_int *closest_int)
{
	t_int			intersection;
	int				found_intersection;
	double			closest_t;

	found_intersection = 0;
	closest_t = INFINITY;
	while (objects != NULL)
	{
		if (intersect(ray, objects->object, objects->type, &intersection)
			&& intersection.t < closest_t)
		{
			*closest_int = intersection;
			closest_int->object = objects;
			closest_t = intersection.t;
			found_intersection = 1;
		}
		objects = objects->next;
	}
	return (found_intersection);
}
