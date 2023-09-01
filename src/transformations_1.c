/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:28:40 by fcullen           #+#    #+#             */
/*   Updated: 2023/09/01 23:02:07 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Rotate the camera's orientation vector around the up vector (y-axis)
// by the given angle in degrees
void	rotate_camera_y(t_camera *cam, double ang_deg)
{
	double	ang_rad;
	double	c;
	double	s;
	t_v3	new_orient;

	ang_rad = deg_to_rad(ang_deg);
	c = cos(ang_rad);
	s = sin(ang_rad);
	new_orient.x = cam->normal_vec->x * c - cam->normal_vec->z * s;
	new_orient.y = cam->normal_vec->y;
	new_orient.z = cam->normal_vec->x * s + cam->normal_vec->z * c;
	*cam->normal_vec = normalize(new_orient);
}

void	rotate_camera_x(t_camera *cam, double ang_deg)
{
	double	ang_rad;
	double	c;
	double	s;
	t_v3	new_orient;

	ang_rad = deg_to_rad(ang_deg);
	c = cos(ang_rad);
	s = sin(ang_rad);
	new_orient.x = cam->normal_vec->x;
	new_orient.y = cam->normal_vec->y * c - cam->normal_vec->z * s;
	new_orient.z = cam->normal_vec->y * s + cam->normal_vec->z * c;
	*cam->normal_vec = normalize(new_orient);
}

void	rotate_plane_y(t_plane *pl, double ang_deg)
{
	double	ang_rad;
	double	c;
	double	s;
	t_v3	new_orient;

	ang_rad = deg_to_rad(ang_deg);
	c = cos(ang_rad);
	s = sin(ang_rad);
	new_orient.x = pl->normal_vec->x * c - pl->normal_vec->z * s;
	new_orient.y = pl->normal_vec->y;
	new_orient.z = pl->normal_vec->x * s + pl->normal_vec->z * c;
	*pl->normal_vec = normalize(new_orient);
}

void	rotate_plane_x(t_plane *pl, double ang_deg)
{
	double	ang_rad;
	double	c;
	double	s;
	t_v3	new_orient;

	ang_rad = deg_to_rad(ang_deg);
	c = cos(ang_rad);
	s = sin(ang_rad);
	new_orient.x = pl->normal_vec->x;
	new_orient.y = pl->normal_vec->y * c - pl->normal_vec->z * s;
	new_orient.z = pl->normal_vec->y * s + pl->normal_vec->z * c;
	*pl->normal_vec = normalize(new_orient);
}

void	rotate_plane_z(t_plane *pl, double ang_deg)
{
	double	ang_rad;
	double	c;
	double	s;
	t_v3	new_orient;

	ang_rad = deg_to_rad(ang_deg);
	c = cos(ang_rad);
	s = sin(ang_rad);
	new_orient.x = pl->normal_vec->x * c - pl->normal_vec->y * s;
	new_orient.y = pl->normal_vec->x * s + pl->normal_vec->y * c;
	new_orient.z = pl->normal_vec->z;
	*pl->normal_vec = normalize(new_orient);
}

// // Rotate the camera's orientation vector around the up vector
// (y-axis) by the given angle in degrees
// void	rotate_camera_y(t_camera *camera, double angle_deg)
// {
// 	double angle_rad;
// 
// 	angle_rad = deg_to_rad(angle_deg);

// 	t_v3 *camera_orientation = camera->normal_vec;
// 	t_v3 new_orientation = {
// 		camera_orientation->x * cos(angle_rad) -
// camera_orientation->z * sin(angle_rad),
// 		camera_orientation->y,
// 		camera_orientation->x * sin(angle_rad) +
// camera_orientation->z * cos(angle_rad)
// 	};
// 	*camera_orientation = normalize(new_orientation);
// }

// void	rotate_camera_x(t_camera *camera, double angle_deg)
// {
// 	double angle_rad = deg_to_rad(angle_deg);

// 	t_v3 *camera_orientation = camera->normal_vec;
// 	t_v3 *camera_up = camera->up;

// 	t_v3 new_orientation = {
// 		camera_orientation->x,
// 		camera_orientation->y * cos(angle_rad) - 
// camera_orientation->z * sin(angle_rad),
// 		camera_orientation->y * sin(angle_rad) + 
// camera_orientation->z * cos(angle_rad)
// 	};

// 	t_v3 new_up = {
// 		camera_up->x,
// 		camera_up->y * cos(angle_rad) - camera_up->z * sin(angle_rad),
// 		camera_up->y * sin(angle_rad) + camera_up->z * cos(angle_rad)
// 	};

// 	*camera_orientation = normalize(new_orientation);
// 	*camera_up = normalize(new_up);
// }