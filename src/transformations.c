/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:28:40 by fcullen           #+#    #+#             */
/*   Updated: 2023/08/29 18:28:36 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Rotate the camera's orientation vector around the up vector (y-axis) by the given angle in degrees
void	rotate_camera_y(t_camera *camera, double angle_deg)
{
	double angle_rad = deg_to_rad(angle_deg);

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

void	rotate_plane_y(t_plane *plane, double angle_deg)
{
	double	angle_rad;
	t_v3	*plane_orientation;
	// t_v3	*new_orientation;

	angle_rad = deg_to_rad(angle_deg);
	plane_orientation = plane->normal_vec;
	t_v3	new_orientation = {
		plane_orientation->x * cos(angle_rad) - plane_orientation->z * sin(angle_rad),
		plane_orientation->y,
		plane_orientation->x * sin(angle_rad) + plane_orientation->z * cos(angle_rad)
	};
	
	*plane_orientation = normalize(new_orientation);
}

void	rotate_plane_x(t_plane *plane, double angle_deg)
{
	double	angle_rad;
	t_v3	*plane_normal;
	// t_v3	*new_orientation;

	angle_rad = deg_to_rad(angle_deg);
	plane_normal = plane->normal_vec;
	t_v3	new_orientation = {
		plane_normal->x,
		plane_normal->y * cos(angle_rad) - plane_normal->z * sin(angle_rad),
		plane_normal->y * sin(angle_rad) + plane_normal->z * cos(angle_rad)
	};
	
	*plane_normal = normalize(new_orientation);
}

// void	rotate_cylinder_y(t_cylinder *cylinder, double angle_deg)
// {
// 	double angle_rad = deg_to_rad(angle_deg);

// 	t_v3 *cylinder_orientation = cylinder->normal_vec;
// 	t_v3 new_orientation = {
// 		cylinder_orientation->x * cos(angle_rad) - cylinder_orientation->z * sin(angle_rad),
// 		cylinder_orientation->y,
// 		cylinder_orientation->x * sin(angle_rad) + cylinder_orientation->z * cos(angle_rad)
// 	};
// 	*cylinder_orientation = normalize(new_orientation);
// }
