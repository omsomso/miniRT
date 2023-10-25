/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaphod <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:28:40 by zaphod           #+#    #+#             */
/*   Updated: 2023/09/26 13:19:47 by zaphod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	rotate_cylinder_y(t_cylinder *cy, double ang_deg)
{
	double	ang_rad;
	double	c;
	double	s;
	t_v3	new_orient;

	ang_rad = deg_to_rad(ang_deg);
	c = cos(ang_rad);
	s = sin(ang_rad);
	new_orient.x = cy->normal->x * c - cy->normal->z * s;
	new_orient.y = cy->normal->y;
	new_orient.z = cy->normal->x * s + cy->normal->z * c;
	*cy->normal = normalize(new_orient);
}

void	rotate_cylinder_x(t_cylinder *cy, double ang_deg)
{
	double	ang_rad;
	double	c;
	double	s;
	t_v3	new_orient;

	ang_rad = deg_to_rad(ang_deg);
	c = cos(ang_rad);
	s = sin(ang_rad);
	new_orient.x = cy->normal->x;
	new_orient.y = cy->normal->y * c - cy->normal->z * s;
	new_orient.z = cy->normal->y * s + cy->normal->z * c;
	*cy->normal = normalize(new_orient);
}

void	rotate_cylinder_z(t_cylinder *cy, double ang_deg)
{
	double	ang_rad;
	double	c;
	double	s;
	t_v3	new_orient;

	ang_rad = deg_to_rad(ang_deg);
	c = cos(ang_rad);
	s = sin(ang_rad);
	new_orient.x = cy->normal->x * c - cy->normal->y * s;
	new_orient.y = cy->normal->x * s + cy->normal->y * c;
	new_orient.z = cy->normal->z;
	*cy->normal = normalize(new_orient);
}
