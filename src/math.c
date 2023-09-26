/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:32:47 by fcullen           #+#    #+#             */
/*   Updated: 2023/09/26 13:15:57 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Add vectors
t_v3	add_v(t_v3 a, t_v3 b)
{
	t_v3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

// Subtract vectors
t_v3	sub_v(t_v3 a, t_v3 b)
{
	t_v3	result;

	result.x = b.x - a.x;
	result.y = b.y - a.y;
	result.z = b.z - a.z;
	return (result);
}

// Multiply Vector (a) by scalar (s)
t_v3	mvs(t_v3 a, double s)
{
	t_v3	result;

	result.x = a.x * s;
	result.y = a.y * s;
	result.z = a.z * s;
	return (result);
}

// Normalize a vector
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

// Distance between two points
float	distance_to_point(t_v3 a, t_v3 b)
{
	float	dx;
	float	dy;
	float	dz;

	dx = b.x - a.x;
	dy = b.y - a.y;
	dz = b.z - a.z;
	return (sqrt(dx * dx + dy * dy + dz * dz));
}
