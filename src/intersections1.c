/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaphod <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:39:07 by zaphod           #+#    #+#             */
/*   Updated: 2023/09/26 15:40:21 by zaphod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Get ray->plane intersection
int	intersect_plane(t_ray ray, t_plane *plane, t_int *intersection)
{
	t_v3	oc;
	float	denominator;
	float	t;

	denominator = dot_p(ray.direction, *(plane->normal));
	if (fabs(denominator) > 0.0001f)
	{
		oc = sub_v(ray.origin, *(plane->point));
		t = dot_p(oc, *(plane->normal)) / denominator;
		if (t >= 0.0f)
		{
			intersection->point = add_v(ray.origin, mvs(ray.direction, t));
			intersection->normal = mvs(*(plane->normal), -1);
			intersection->t = t;
			return (1);
		}
	}
	return (0);
}

// Get ray->sphere intersection
int	intersect_sphere(t_ray ray, t_sphere *sphere, t_int *intersection)
{
	t_v3	oc;
	float	a;
	float	b;
	float	c;
	float	t;

	oc = sub_v(*(sphere->center), ray.origin);
	a = dot_p(ray.direction, ray.direction);
	b = 2.0 * dot_p(oc, ray.direction);
	c = dot_p(oc, oc) - (sphere->radius * sphere->radius);
	if (compute_discriminant(a, b, c) < 0)
		return (0);
	t = calculate_t(a, b, compute_discriminant(a, b, c));
	if (t < 0)
		return (0);
	update_intersection(intersection, ray, t, sphere->center);
	return (1);
}

// Calls intersection function depending on object type
int	intersect(t_ray ray, void *object, t_type type, t_int *intersection)
{
	if (type == SPHERE)
		return (intersect_sphere(ray, (t_sphere *)object, intersection));
	else if (type == PLANE)
		return (intersect_plane(ray, (t_plane *)object, intersection));
	else if (type == CYLINDER)
		return (intersect_cylinder(ray, (t_cylinder *)object, intersection));
	else
		return (0);
}

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
