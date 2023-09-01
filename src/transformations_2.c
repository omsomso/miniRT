/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:28:40 by fcullen           #+#    #+#             */
/*   Updated: 2023/09/01 23:01:26 by kpawlows         ###   ########.fr       */
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
	new_orient.x = cy->normal_vec->x * c - cy->normal_vec->z * s;
	new_orient.y = cy->normal_vec->y;
	new_orient.z = cy->normal_vec->x * s + cy->normal_vec->z * c;
	*cy->normal_vec = normalize(new_orient);
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
	new_orient.x = cy->normal_vec->x;
	new_orient.y = cy->normal_vec->y * c - cy->normal_vec->z * s;
	new_orient.z = cy->normal_vec->y * s + cy->normal_vec->z * c;
	*cy->normal_vec = normalize(new_orient);
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
	new_orient.x = cy->normal_vec->x * c - cy->normal_vec->y * s;
	new_orient.y = cy->normal_vec->x * s + cy->normal_vec->y * c;
	new_orient.z = cy->normal_vec->z;
	*cy->normal_vec = normalize(new_orient);
}
