/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:31:48 by kpawlows          #+#    #+#             */
/*   Updated: 2023/09/01 22:02:54 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/gui.h"

// Returns selected row of an ui element based on mouse_pos.y
int	find_selected_param(t_pos mouse_pos)
{
	float	sel_par;
	float	sel_row;

	sel_row = 0;
	while (sel_row * GUI_EL_HEIGHT < mouse_pos.y)
		sel_row++;
	sel_row--;
	sel_par = (mouse_pos.y - (sel_row * GUI_EL_HEIGHT)) / GUI_EL_PAR_HEIGHT;
	sel_par -= GUI_EL_PAR_OFFSET;
	return (sel_par);
}

// Returns selected ui element id based on mouse pos
int	find_selected_ui_element(t_data *data, t_pos mouse_pos)
{
	int	obj_selected;
	int	max_horizontal_el;

	obj_selected = 0;
	max_horizontal_el = 0;
	obj_selected = (mouse_pos.x / GUI_EL_WIDTH);
	while (max_horizontal_el < GUI_MAX_WIDTH)
		max_horizontal_el += GUI_EL_WIDTH;
	max_horizontal_el = max_horizontal_el / GUI_EL_WIDTH;
	obj_selected += ((mouse_pos.y / GUI_EL_HEIGHT) * max_horizontal_el);
	if (obj_selected > data->gui->obj_count)
		return (-1);
	return (obj_selected + 1);
}

// Finds object in obj linked list by id, advances the list
t_object	*find_object(t_object *obj, int id)
{
	int			count;

	count = 0;
	while (obj)
	{
		count++;
		if (count == id)
			return (obj);
		obj = obj->next;
	}
	return (NULL);
}

// Offsets draw_pos to higher y values if x exceeds GUI_MAX_WIDTH
void	wrap_gui(t_gui *gui)
{
	gui->draw_pos.x += GUI_EL_WIDTH;
	if (gui->draw_pos.x >= GUI_MAX_WIDTH)
	{
		gui->draw_pos.x = 0;
		gui->draw_pos.y += GUI_EL_HEIGHT;
	}
}
