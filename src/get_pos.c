/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:36:16 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/30 12:38:20 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Returns pos coordinates of a sphere
t_v3	get_pos_sphere(t_sphere *sphere)
{
	t_v3	pos;

	pos.x = sphere->center->x;
	pos.y = sphere->center->y;
	pos.z = sphere->center->z;
	return (pos);
}

// Returns pos coordinates of a plane
t_v3	get_pos_plane(t_plane *plane)
{
	t_v3	pos;

	pos.x = plane->point->x;
	pos.y = plane->point->y;
	pos.z = plane->point->z;
	return (pos);
}

// Returns pos coordinates of a cylinder
t_v3	get_pos_cylinder(t_cylinder *cylinder)
{
	t_v3	pos;

	pos.x = cylinder->center->x;
	pos.y = cylinder->center->y;
	pos.z = cylinder->center->z;
	return (pos);
}
// Returns pos coordinates of the light
t_v3	get_light_pos(t_light *light)
{
	t_v3	pos;

	pos.x = light->pos->x;
	pos.y = light->pos->y;
	pos.z = light->pos->z;
	return (pos);
}

// Returns pos coordinates of the camera
t_v3	get_camera_pos(t_camera *camera)
{
	t_v3	pos;

	pos.x = camera->pos->x;
	pos.y = camera->pos->y;
	pos.z = camera->pos->z;
	return (pos);
}

// Returns normal vector of a plane
t_v3	get_rot_plane(t_plane *plane)
{
	t_v3	rot;

	rot.x = plane->normal_vec->x;
	rot.y = plane->normal_vec->y;
	rot.z = plane->normal_vec->z;
	return (rot);
}

// Returns normal vector of a cylinder
t_v3	get_rot_cylinder(t_cylinder *cylinder)
{
	t_v3	rot;

	rot.x = cylinder->normal_vec->x;
	rot.y = cylinder->normal_vec->y;
	rot.z = cylinder->normal_vec->z;
	return (rot);
}