/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_objects_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:10:00 by kpawlows          #+#    #+#             */
/*   Updated: 2023/10/22 19:50:24 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gui.h"

void	modify_camera_b(t_data *data, t_gui *gui, int button, int sel)
{
	if (sel == 5 && button == 5)
	{
		rotate_camera_x(data->camera, -1);
		gui->cam_ang_offset.x -= 1;
	}
	else if (sel == 5 && button == 4)
	{
		rotate_camera_x(data->camera, 1);
		gui->cam_ang_offset.x += 1;
	}
	else if (sel == 6 && button == 5)
	{
		rotate_camera_y(data->camera, -1);
		gui->cam_ang_offset.y += 1;
	}
	else if (sel == 6 && button == 4)
	{
		rotate_camera_y(data->camera, 1);
		gui->cam_ang_offset.y -= 1;
	}
}

void	modify_camera(t_data *data, t_gui *gui, int button, int sel)
{
	if (sel == 1 && button == 4)
		data->camera->pos->x -= MOD_POS;
	else if (sel == 1 && button == 5)
		data->camera->pos->x += MOD_POS;
	else if (sel == 2 && button == 4)
		data->camera->pos->y -= MOD_POS;
	else if (sel == 2 && button == 5)
		data->camera->pos->y += MOD_POS;
	else if (sel == 3 && button == 4)
		data->camera->pos->z -= MOD_POS;
	else if (sel == 3 && button == 5)
		data->camera->pos->z += MOD_POS;
	else if (sel == 4 && button == 4)
		data->camera->fov -= MOD_FOV;
	else if (sel == 4 && button == 5)
		data->camera->fov += MOD_FOV;
	cut_values_int(&data->camera->fov, 180, 0);
	modify_camera_b(data, gui, button, sel);
}

void	modify_cylinder_c(t_cylinder *cy, int button, int sel)
{
	if (sel == 7 && button == 5)
	{
		rotate_cylinder_z(cy, -MOD_ANG);
		cy->cy_ang_offset.z += MOD_ANG;
	}
	else if (sel == 7 && button == 4)
	{
		rotate_cylinder_z(cy, MOD_ANG);
		cy->cy_ang_offset.z -= MOD_ANG;
	}
	if (sel == 8 && button == 4)
		cy->height -= MOD_POS;
	else if (sel == 8 && button == 5)
		cy->height += MOD_POS;
	cut_values(&cy->diameter, 2147483647, 0.01);
	cut_values(&cy->height, 2147483647, 0.01);
}

void	modify_cylinder_b(t_cylinder *cy, int button, int sel)
{
	if (sel == 5 && button == 5)
	{
		rotate_cylinder_x(cy, -MOD_ANG);
		cy->cy_ang_offset.x += MOD_ANG;
	}
	else if (sel == 5 && button == 4)
	{
		rotate_cylinder_x(cy, MOD_ANG);
		cy->cy_ang_offset.x -= MOD_ANG;
	}
	else if (sel == 6 && button == 5)
	{
		rotate_cylinder_y(cy, -MOD_ANG);
		cy->cy_ang_offset.y += MOD_ANG;
	}
	else if (sel == 6 && button == 4)
	{
		rotate_cylinder_y(cy, MOD_ANG);
		cy->cy_ang_offset.y -= MOD_ANG;
	}
	modify_cylinder_c(cy, button, sel);
}

void	modify_cylinder(t_cylinder *cy, int button, int sel)
{
	if (sel == 1 && button == 4)
		cy->center->x -= MOD_POS;
	else if (sel == 1 && button == 5)
		cy->center->x += MOD_POS;
	else if (sel == 2 && button == 4)
		cy->center->y -= MOD_POS;
	else if (sel == 2 && button == 5)
		cy->center->y += MOD_POS;
	else if (sel == 3 && button == 4)
		cy->center->z -= MOD_POS;
	else if (sel == 3 && button == 5)
		cy->center->z += MOD_POS;
	else if (sel == 4 && button == 4)
		cy->radius -= MOD_RADIUS;
	else if (sel == 4 && button == 5)
		cy->radius += MOD_RADIUS;
	modify_cylinder_b(cy, button, sel);
}
