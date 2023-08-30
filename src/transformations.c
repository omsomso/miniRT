/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:28:40 by fcullen           #+#    #+#             */
/*   Updated: 2023/08/30 12:39:10 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Rotate the camera's orientation vector around the up vector (y-axis) by the given angle in degrees
void	rotate_camera_y(t_camera *camera, double angle_deg)
{
	double angle_rad;
	
	angle_rad = deg_to_rad(angle_deg);

	t_v3 *camera_orientation = camera->normal_vec;
	t_v3 new_orientation = {
		camera_orientation->x * cos(angle_rad) - camera_orientation->z * sin(angle_rad),
		camera_orientation->y,
		camera_orientation->x * sin(angle_rad) + camera_orientation->z * cos(angle_rad)
	};
	*camera_orientation = normalize(new_orientation);
}

void	rotate_camera_x(t_camera *camera, double angle_deg)
{
	double angle_rad = deg_to_rad(angle_deg);

	t_v3 *camera_orientation = camera->normal_vec;
	t_v3 *camera_up = camera->up;

	t_v3 new_orientation = {
		camera_orientation->x,
		camera_orientation->y * cos(angle_rad) - camera_orientation->z * sin(angle_rad),
		camera_orientation->y * sin(angle_rad) + camera_orientation->z * cos(angle_rad)
	};

	t_v3 new_up = {
		camera_up->x,
		camera_up->y * cos(angle_rad) - camera_up->z * sin(angle_rad),
		camera_up->y * sin(angle_rad) + camera_up->z * cos(angle_rad)
	};

	*camera_orientation = normalize(new_orientation);
	*camera_up = normalize(new_up);
}

void	rotate_plane_y(t_plane *pl, double ang_deg)
{
	double	ang_rad;
	float	cos_theta;
	float	sin_theta;
	t_v3	new_orient;
	
	ang_rad = deg_to_rad(ang_deg);
	cos_theta = cos(ang_rad);
	sin_theta = sin(ang_rad);
	new_orient.x = pl->normal_vec->x * cos_theta - pl->normal_vec->z * sin_theta;
	new_orient.y = pl->normal_vec->y;
	new_orient.z = pl->normal_vec->x * sin_theta + pl->normal_vec->z * cos_theta;
	*pl->normal_vec = normalize(new_orient);
}

void 	rotate_plane_x(t_plane *pl, double ang_deg)
{
	double	ang_rad;
	float	cos_theta;
	float	sin_theta;
	t_v3	new_orient;
	
	ang_rad = deg_to_rad(ang_deg);
	cos_theta = cos(ang_rad);
	sin_theta = sin(ang_rad);
	new_orient.x = pl->normal_vec->x;
	new_orient.y = pl->normal_vec->y * cos_theta - pl->normal_vec->z * sin_theta;
	new_orient.z = pl->normal_vec->y * sin_theta + pl->normal_vec->z * cos_theta;
	*pl->normal_vec = normalize(new_orient);
}

void	rotate_plane_z(t_plane *pl, double ang_deg)
{
	double	ang_rad;
	float	cos_theta;
	float	sin_theta;
	t_v3	new_orient;
	
	ang_rad = deg_to_rad(ang_deg);
	cos_theta = cos(ang_rad);
	sin_theta = sin(ang_rad);
	new_orient.x = pl->normal_vec->x * cos_theta - pl->normal_vec->y * sin_theta;
	new_orient.y = pl->normal_vec->x * sin_theta + pl->normal_vec->y * cos_theta;
	new_orient.z = pl->normal_vec->z;
	*pl->normal_vec = normalize(new_orient);
}

void	rotate_cylinder_y(t_cylinder *cy, double ang_deg)
{
	double	ang_rad;
	float	cos_theta;
	float	sin_theta;
	t_v3	new_orient;
	
	ang_rad = deg_to_rad(ang_deg);
	cos_theta = cos(ang_rad);
	sin_theta = sin(ang_rad);
	new_orient.x = cy->normal_vec->x * cos_theta - cy->normal_vec->z * sin_theta;
	new_orient.y = cy->normal_vec->y;
	new_orient.z = cy->normal_vec->x * sin_theta + cy->normal_vec->z * cos_theta;
	*cy->normal_vec = normalize(new_orient);
}

void	rotate_cylinder_x(t_cylinder *cy, double ang_deg)
{
	double	ang_rad;
	float	cos_theta;
	float	sin_theta;
	t_v3	new_orient;
	
	ang_rad = deg_to_rad(ang_deg);
	cos_theta = cos(ang_rad);
	sin_theta = sin(ang_rad);
	new_orient.x = cy->normal_vec->x;
	new_orient.y = cy->normal_vec->y * cos_theta - cy->normal_vec->z * sin_theta;
	new_orient.z = cy->normal_vec->y * sin_theta + cy->normal_vec->z * cos_theta;
	*cy->normal_vec = normalize(new_orient);
}

void	rotate_cylinder_z(t_cylinder *cy, double ang_deg)
{
	double	ang_rad;
	float	cos_theta;
	float	sin_theta;
	t_v3	new_orient;
	
	ang_rad = deg_to_rad(ang_deg);
	cos_theta = cos(ang_rad);
	sin_theta = sin(ang_rad);
	new_orient.x = cy->normal_vec->x * cos_theta - cy->normal_vec->y * sin_theta;
	new_orient.y = cy->normal_vec->x * sin_theta + cy->normal_vec->y * cos_theta;
	new_orient.z = cy->normal_vec->z;
	*cy->normal_vec = normalize(new_orient);
}
