/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:31:48 by kpawlows          #+#    #+#             */
/*   Updated: 2023/09/01 22:03:23 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gui.h"

// Counts objects for ui (adds 2 for C and L)
int	count_objects(t_object *objects)
{
	int			count;
	t_object	*obj;

	count = 2;
	obj = objects;
	while (obj)
	{
		count++;
		obj = obj->next;
	}
	return (count);
}

// Returns ui window height based on modifiable parameters
int	compute_gui_height(int obj_count)
{
	int	height;

	height = 0;
	while (obj_count > 0)
	{
		obj_count -= (GUI_MAX_WIDTH / GUI_EL_WIDTH);
		height += GUI_EL_HEIGHT;
	}
	return (height);
}

// Returns final ui window width based on GUI_MAX_WIDTH
int	compute_gui_width(int obj_count)
{
	int	width;

	width = 0;
	while (obj_count > 0 && width < GUI_MAX_WIDTH)
	{
		obj_count -= 1;
		width += GUI_EL_WIDTH;
	}
	return (width);
}

// Updates the gui struct for each ui redraw
t_gui	*update_gui_struct(t_data *data, t_gui *gui, t_pos mouse_pos)
{
	gui->mouse_pos = mouse_pos;
	gui->sel_bckg = find_selected_ui_element(data, mouse_pos);
	if (gui->sel_bckg < 0)
		gui->sel_bckg = -1;
	gui->sel_par = find_selected_param(mouse_pos);
	if (gui->sel_par < 0)
		gui->sel_par = -1;
	gui->draw_pos.x = 0;
	gui->draw_pos.y = 0;
	return (gui);
}

// Inits gui struct
t_gui	*init_gui_struct(t_data *data)
{
	t_gui	*gui;

	gui = malloc(sizeof(t_gui));
	if (!gui)
		return (NULL);
	gui->cam_ang_offset.x = 0;
	gui->cam_ang_offset.y = 0;
	gui->pics = data->pics;
	gui->sel_bckg = 0;
	if (gui->sel_bckg < 0)
		gui->sel_bckg = -1;
	gui->objects = data->objects;
	gui->mlx = data->mlx;
	gui->draw_pos.x = 0;
	gui->draw_pos.y = 0;
	gui->obj_count = count_objects(gui->objects);
	data->gui = gui;
	gui->data = data;
	return (gui);
}
