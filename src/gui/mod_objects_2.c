/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_objects_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:13:12 by kpawlows          #+#    #+#             */
/*   Updated: 2023/09/26 13:19:47 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	modify_plane_c(t_gui *gui, t_plane *plane, int button, int sel)
{
	if (sel == 7 && button == 5)
	{
		rotate_plane_z(plane, -MOD_ANG);
		plane->pl_ang_offset.z += MOD_ANG;
	}
	else if (sel == 7 && button == 4)
	{
		rotate_plane_z(plane, MOD_ANG);
		plane->pl_ang_offset.z -= MOD_ANG;
	}
	*plane->normal = normalize(*plane->normal);
}

void	modify_plane_b(t_gui *gui, t_plane *plane, int button, int sel)
{
	if (sel == 5 && button == 5)
	{
		rotate_plane_x(plane, -MOD_ANG);
		plane->pl_ang_offset.x += MOD_ANG;
	}
	else if (sel == 5 && button == 4)
	{
		rotate_plane_x(plane, MOD_ANG);
		plane->pl_ang_offset.x -= MOD_ANG;
	}
	else if (sel == 6 && button == 5)
	{
		rotate_plane_y(plane, -MOD_ANG);
		plane->pl_ang_offset.y += MOD_ANG;
	}
	else if (sel == 6 && button == 4)
	{
		rotate_plane_y(plane, MOD_ANG);
		plane->pl_ang_offset.y -= MOD_ANG;
	}
	modify_plane_c(gui, plane, button, sel);
}

void	modify_plane(t_gui *gui, t_plane *plane, int button, int sel)
{
	if (sel == 1 && button == 4)
		plane->point->x -= MOD_POS;
	else if (sel == 1 && button == 5)
		plane->point->x += MOD_POS;
	else if (sel == 2 && button == 4)
		plane->point->y -= MOD_POS;
	else if (sel == 2 && button == 5)
		plane->point->y += MOD_POS;
	else if (sel == 3 && button == 4)
		plane->point->z -= MOD_POS;
	else if (sel == 3 && button == 5)
		plane->point->z += MOD_POS;
	modify_plane_b(gui, plane, button, sel);
}

void	modify_sphere(t_sphere *sphere, int button, int sel_param)
{
	if (sel_param == 1 && button == 4)
		sphere->center->x -= MOD_POS;
	else if (sel_param == 1 && button == 5)
		sphere->center->x += MOD_POS;
	else if (sel_param == 2 && button == 4)
		sphere->center->y -= MOD_POS;
	else if (sel_param == 2 && button == 5)
		sphere->center->y += MOD_POS;
	else if (sel_param == 3 && button == 4)
		sphere->center->z -= MOD_POS;
	else if (sel_param == 3 && button == 5)
		sphere->center->z += MOD_POS;
	else if (sel_param == 4 && button == 4)
		sphere->radius -= MOD_RADIUS;
	else if (sel_param == 4 && button == 5)
		sphere->radius += MOD_RADIUS;
	cut_values(&sphere->radius, 100000, 0.1);
}

void	modify_light(t_data *data, int button, int sel)
{
	if (sel == 1 && button == 4)
		data->light->pos->x -= MOD_POS;
	else if (sel == 1 && button == 5)
		data->light->pos->x += MOD_POS;
	else if (sel == 2 && button == 4)
		data->light->pos->y -= MOD_POS;
	else if (sel == 2 && button == 5)
		data->light->pos->y += MOD_POS;
	else if (sel == 3 && button == 4)
		data->light->pos->z -= MOD_POS;
	else if (sel == 3 && button == 5)
		data->light->pos->z += MOD_POS;
}
