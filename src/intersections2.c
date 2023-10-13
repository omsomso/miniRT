/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:24:35 by fcullen           #+#    #+#             */
/*   Updated: 2023/10/13 17:39:42 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Check caps intersection
float	check_caps(t_ray ray, t_cylinder *cylinder,
		float oc_dot_n, float dir_dot_n)
{
	float	t_caps;
	float	t_cap;
	t_v3	p;
	t_v3	to_center;
	int		j;

	t_caps = INFINITY;
	j = 0;
	while (j < 2)
	{
		t_cap = (cylinder->cap_offsets[j] - oc_dot_n) / dir_dot_n;
		if (t_cap > 0)
		{
			p = add_v(ray.origin, mvs(ray.direction, t_cap));
			to_center = sub_v(*(cylinder->center), p);
			to_center = sub_v(to_center,
					mvs(*(cylinder->normal),
						dot_p(to_center, *(cylinder->normal))));
			if (dot_p(to_center, to_center)
				<= cylinder->radius * cylinder->radius && t_cap < t_caps)
				t_caps = t_cap;
		}
		j++;
	}
	return (t_caps);
}

// Set normal at intersection
int	set_intersection_normal(t_cy_params *params, float t_final)
{
	t_v3	v_to_int;
	t_v3	proj_v;
	t_v3	normal;

	if (t_final == params->t_body)
	{
		v_to_int = sub_v(params->intersection->point,
				*(params->cylinder->center));
		proj_v = mvs(*(params->cylinder->normal),
				dot_p(v_to_int, *(params->cylinder->normal)));
		normal = sub_v(v_to_int, proj_v);
		params->intersection->normal = normalize(mvs(normal, -1));
	}
	else
	{
		if (t_final == params->t_caps && params->oc_dot_n > 0)
			params->intersection->normal = mvs(*(params->cylinder->normal), -1);
		else
			params->intersection->normal = *(params->cylinder->normal);
	}
	return (1);
}

// Compute final intersection depending on whether it is on body or cap
int	compute_final(t_cy_params *params)
{
	float	t_final;

	if (params->t_body == INFINITY && params->t_caps == INFINITY)
		return (0);
	if (params->t_caps == INFINITY
		|| (params->t_body < INFINITY && params->t_body < params->t_caps))
		t_final = params->t_body;
	else
		t_final = params->t_caps;
	params->intersection->point = add_v(params->ray.origin,
			mvs(params->ray.direction, t_final));
	params->intersection->t = t_final;
	return (set_intersection_normal(params, t_final));
}

// Get ray->cylinder intersection
int	intersect_cylinder(t_ray ray, t_cylinder *cylinder, t_int *intersection)
{
	t_coeff		coeffs;
	float		discriminant;
	float		t_body;
	float		t_caps;
	t_cy_params	params;

	coeffs = compute_abc(ray, cylinder);
	discriminant = compute_discriminant(coeffs.a, coeffs.b, coeffs.c);
	t_body = check_body(ray, cylinder, coeffs, discriminant);
	params.oc = sub_v(*(cylinder->center), ray.origin);
	params.dir_dot_n = dot_p(ray.direction, *(cylinder->normal));
	params.oc_dot_n = dot_p(params.oc, *(cylinder->normal));
	t_caps = check_caps(ray, cylinder, params.oc_dot_n, params.dir_dot_n);
	params.ray = ray;
	params.cylinder = cylinder;
	params.t_body = t_body;
	params.t_caps = t_caps;
	params.intersection = intersection;
	return (compute_final(&params));
}

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
