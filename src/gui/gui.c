/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:52:43 by kpawlows          #+#    #+#             */
/*   Updated: 2023/09/01 23:03:17 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gui.h"

// Calls relevant ui functions and retraces based on user mouse input
int	gui(t_data *data, t_gui *gui, t_pos mouse_pos, int button)
{
	update_gui_struct(data, gui, mouse_pos);
	modify_objects(data, data->gui, button);
	draw_gui(data, data->gui);
	conditional_retrace(data, button);
	return (0);
}

// Modifies object parameters based on user input
int	modify_objects(t_data *data, t_gui *gui, int button)
{
	t_object	*obj;

	if (gui->sel_par && (button == 4 || button == 5))
	{
		obj = find_object(data->objects, gui->sel_bckg);
		if (gui->sel_bckg == gui->obj_count - 1)
			modify_light(data, button, gui->sel_par);
		else if (gui->sel_bckg == gui->obj_count)
			modify_camera(data, data->gui, button, gui->sel_par);
		if (!obj)
			return (0);
		else if (obj->type == SPHERE)
			modify_sphere(obj->object, button, gui->sel_par);
		else if (obj->type == PLANE)
			modify_plane(gui, obj->object, button, gui->sel_par);
		else if (obj->type == CYLINDER)
			modify_cylinder(obj->object, button, gui->sel_par);
	}
	return (0);
}

// Draws ui window
int	draw_gui(t_data *data, t_gui *gui)
{
	mlx_clear_window(data->mlx->ptr, data->mlx->win_gui);
	draw_gui_loop(gui);
	draw_light_ctrls(data->light, gui, data->mlx);
	draw_camera_ctrls(data->camera, gui, data->mlx);
	fill_background(gui, gui->mlx);
	return (0);
}

// Draws ui elements for each object in data->objects
int	draw_gui_loop(t_gui *gui)
{
	t_object	*current;
	int			obj_id;

	obj_id = 0;
	current = gui->objects;
	while (current)
	{
		obj_id++;
		draw_background(gui, gui->mlx, obj_id);
		gui->draw_pos.x += GUI_EL_MARGIN;
		if (current->type == SPHERE)
			draw_sp_ctrls(gui, current->object, obj_id);
		else if (current->type == PLANE)
			draw_pl_ctrls(gui, current->object, obj_id);
		else if (current->type == CYLINDER)
			draw_cy_ctrls(gui, current->object, obj_id);
		current = current->next;
		gui->draw_pos.x -= GUI_EL_MARGIN;
		wrap_gui(gui);
	}
	return (0);
}

// Calls generate rays if auto_retrace is on or if right click
void	conditional_retrace(t_data *data, int button)
{
	if (data->auto_retrace)
		generate_rays(data);
	else if (button == 2 || button == -1)
		generate_rays(data);
}
