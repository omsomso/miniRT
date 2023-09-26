/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:05:23 by fcullen           #+#    #+#             */
/*   Updated: 2023/09/26 14:35:59 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	v3_equal(t_v3 v1, t_v3 v2)
{
	return (fabs(v1.x - v2.x) < EPSILON
		&& fabs(v1.y - v2.y) < EPSILON
		&& fabs(v1.z - v2.z) < EPSILON);
}

t_v3	get_orthogonal(t_v3 v)
{
	if (v.x != 0 || v.y != 0)
		return (new_v3(-v.y, v.x, 0));
	else
		return (new_v3(0, -v.z, 0));
}

t_v3	multiply_matrix_vector(const t_matrix4 matrix, const t_v3 v)
{
	t_v3	res;

	res.x = matrix.m[0][0] * v.x + matrix.m[0][1] * v.y + matrix.m[0][2] * v.z;
	res.y = matrix.m[1][0] * v.x + matrix.m[1][1] * v.y + matrix.m[1][2] * v.z;
	res.z = matrix.m[2][0] * v.x + matrix.m[2][1] * v.y + matrix.m[2][2] * v.z;
	return (res);
}

t_v3	calculate_sphere_normal(t_v3 sphere_center, t_v3 point_on_surface)
{
	t_v3	surface_to_center;
	t_v3	normaltor;

	surface_to_center = sub_v(sphere_center, point_on_surface);
	normaltor = normalize(surface_to_center);
	return (normaltor);
}

float	compute_discriminant(float a, float b, float c)
{
	float	discriminant;

	discriminant = b * b - 4 * a * c;
	return (discriminant);
}
