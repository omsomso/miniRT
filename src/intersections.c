/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:33:41 by fcullen           #+#    #+#             */
/*   Updated: 2023/09/26 14:47:26 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Find distance along ray where there is an intersection
float	calculate_t(float a, float b, float discriminant)
{
	float	t1;
	float	t2;
	float	t;

	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	t = fmin(t1, t2);
	if (t < 0)
		t = fmax(t1, t2);
	return (t);
}

// Update intersection point and get normal
void	update_intersection(t_int *intersection,
					t_ray ray, float t, t_v3 *center)
{
	t_v3	point;
	t_v3	normal;

	point = add_v(ray.origin, mvs(ray.direction, t));
	normal = normalize(sub_v(point, *center));
	intersection->point = point;
	intersection->normal = normal;
	intersection->t = t;
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

// Compute coefficients of a quadratic equation
t_coeff	compute_abc(t_ray ray, t_cylinder *cylinder)
{
	t_coeff	coeffs;
	t_v3	oc;
	float	dir_dot_n;
	float	oc_dot_n;

	oc = sub_v(*(cylinder->center), ray.origin);
	dir_dot_n = dot_p(ray.direction, *(cylinder->normal));
	oc_dot_n = dot_p(oc, *(cylinder->normal));
	coeffs.a = dot_p(ray.direction, ray.direction)
		- dir_dot_n * dir_dot_n;
	coeffs.b = 2 * (dot_p(ray.direction, oc)
			- dir_dot_n * oc_dot_n);
	coeffs.c = dot_p(oc, oc) - oc_dot_n * oc_dot_n
		- cylinder->radius * cylinder->radius;
	return (coeffs);
}

// Check for cylinder body intersection
float	check_body(t_ray ray, t_cylinder *cylinder,
		t_coeff coeffs, float discriminant)
{
	float	t_body;
	float	t;
	t_v3	p;
	float	y;
	int		i;

	t_body = INFINITY;
	if (discriminant < 0)
		return (t_body);
	i = 0;
	while (i < 2)
	{
		t = (-coeffs.b - sqrt(discriminant)) / (2 * coeffs.a);
		if (i == 1)
			t = (-coeffs.b + sqrt(discriminant)) / (2 * coeffs.a);
		p = add_v(ray.origin, mvs(ray.direction, t));
		y = dot_p(sub_v(*(cylinder->center), p),
				*(cylinder->normal));
		if (y > cylinder->cap_offsets[0] && y < cylinder->cap_offsets[1]
			&& t < t_body && t > 0)
			t_body = t;
		i++;
	}
	return (t_body);
}
