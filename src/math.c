/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:32:47 by fcullen           #+#    #+#             */
/*   Updated: 2023/09/01 22:07:36 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_v3	add_vectors(t_v3 a, t_v3 b)
{
	t_v3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_v3	subtract_vectors(t_v3 a, t_v3 b)
{
	t_v3	result;

	result.x = b.x - a.x;
	result.y = b.y - a.y;
	result.z = b.z - a.z;
	return (result);
}

t_v3	multiply_vector_scalar(t_v3 a, double s)
{
	t_v3	result;

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

float	deg_to_rad(float deg)
{
	return ((deg * M_PI) / 180);
}

t_v3 new_v3(float x, float y, float z)
{
	t_v3 new_vector;

	new_vector.x = x;
	new_vector.y = y;
	new_vector.z = z;
	return (new_vector);
}

// Function to check if two vectors are equal
int v3_equal(t_v3 v1, t_v3 v2)
{
	return fabs(v1.x - v2.x) < EPSILON && fabs(v1.y - v2.y) < EPSILON && fabs(v1.z - v2.z) < EPSILON;
}

t_v3 get_orthogonal(t_v3 v)
{
	if (v.x != 0 || v.y != 0)
		return new_v3(-v.y, v.x, 0);
	else
		return new_v3(0, -v.z, 0);
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
