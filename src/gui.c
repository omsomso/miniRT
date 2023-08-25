/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:52:43 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/26 01:24:04 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	calculate_selected_object(t_data *data, int x, int y)
{
	int	obj_count;
	int	obj_selected;

	obj_selected = 0;
	obj_count = count_objects(data->objects);
	obj_selected = (x / 100) + (y / 100) * 5;
	if (obj_selected > obj_count)
		return (-1);
	return (obj_selected + 1);
}

int handle_mouse(int button, int x, int y, t_data *data)
{
	printf("Mouse button %d pressed at %d, %d\n", button, x, y);
	draw_gui(data, calculate_selected_object(data, x, y));
	return (0);
}

int	draw_button(t_data *data, int x, int y, int color)
{
	mlx_put_image_to_window(data->mlx->ptr, data->mlx->win_gui, data->mlx->bckg, x, y);
	return (0);
}

int	draw_cy_ctrls(t_data *data, t_object *cylinder, int x, int y)
{
	(void)data;
		printf("CYLINDER\n");
	mlx_string_put(data->mlx->ptr, data->mlx->win_gui, x, y, 0xFFFFFF, "CYLINDER");
	// mlx_string_put(data->mlx->ptr, data->mlx->win_gui, x, y, 0xFFFFFF, "CYLINDER");
	return (0);
}

int	draw_pl_ctrls(t_data *data, t_object *plane, int x, int y)
{
	(void)data;
		printf("PLANE\n");
	mlx_string_put(data->mlx->ptr, data->mlx->win_gui, x, y, 0xFFFFFF, "PLANE");
	return (0);
}

int	draw_sp_ctrls(t_data *data, t_object *sphere, int x, int y, int sel, int sp_count)
{
	char		*count_str;
	char		*s;

	printf("sel: %d, count: %d\n", sel, sp_count);
	count_str = ft_itoa(sp_count);
	s = ft_strjoin_fs("SPHERE ", count_str);
	if (!s)
		return (1);
	// printf("SPHERE\n");
	// mlx_string_put(data->mlx->ptr, data->mlx->win_gui, x, y, 0xFFFFFF, "SPHERE");
	mlx_put_image_to_window(data->mlx->ptr, data->mlx->win_gui, data->mlx->bckg, x, y);
	if (sp_count == sel)
		mlx_put_image_to_window(data->mlx->ptr, data->mlx->win_gui, data->mlx->sel, x, y);

	mlx_string_put(data->mlx->ptr, data->mlx->win_gui, x + 10, y + 20, 0xFFFFFF, s);
	free(s);
	return (0);
}

int	count_objects(t_object *objects)
{
	int			count;
	t_object	*obj;

	count = 0;
	obj = objects;
	while (obj)
	{
		count++;
		obj = obj->next;
	}
	return (count);
}

int	calculate_gui_height(int obj_count)
{
	int	height;

	height = 0;
	while (obj_count > 0)
	{
		obj_count -= 6;
		height += 100;
	}
	return (height);
}

// int	create_gui_elements(t_data *data)
// {
// 	t_gui_el	*gui_element;
// 	int	sp_count = 0;
// 	int	pl_count = 0;
// 	int	cy_count = 0;

// 	gui_element = malloc(sizeof(t_gui_el));
// 	if (!gui_element)
// 		return (1);
// 	while (obj)
// 	{
// 		if (obj->type == SPHERE)
// 		{
// 			gui_element->type = SPHERE;
// 			gui_element->id = count;
// 			gui_element->name = "SPHERE";
// 		}
// 		else if (obj->type == PLANE)
// 		{
// 			gui_element->type = PLANE;
// 			gui_element->id = count;
// 			gui_element->name = "PLANE";
// 		}
// 		else if (obj->type == CYLINDER)
// 		{
// 			gui_element->type = CYLINDER;
// 			gui_element->id = count;
// 			gui_element->name = "CYLINDER";
// 		}
// 			draw_sp_ctrls(data, obj, x, y, sel);
// 		else if (obj->type == PLANE)
// 			draw_pl_ctrls(data, obj, x, y);
// 		else if (obj->type == CYLINDER)
// 			draw_cy_ctrls(data, obj, x, y);
// 		obj = obj->next;
// 		x += 100;
// 		if (x > 500)
// 		{
// 			x = 0;
// 			y += 100;
// 		}
// 	}
// 	return (0);
// }

int	draw_gui(t_data *data, int sel)
{
	t_object	*obj;
	int			x;
	int			y;
	int			count;
	int			sp_count;
	int			pl_count;
	int			cy_count;

	// create_gui_elements(data);
	// data->mlx->sphere = mlx_xpm_file_to_image(data->mlx->ptr, "assets/sph.xpm", &x, &y);
	// data->mlx->sphere = mlx_png_file_to_image(data->mlx->ptr, "assets/sphere.png", &x, &y);
	x = 0;
	y = 0;
	sp_count = 0;
	// printf("%d\n", *sp_count);
	obj = data->objects;
	while (obj)
	{
		count++;
		if (obj->type == SPHERE)
		{
			sp_count++;
			draw_sp_ctrls(data, obj, x, y, sel, sp_count);
		}
		else if (obj->type == PLANE)
			draw_pl_ctrls(data, obj, x, y);
		else if (obj->type == CYLINDER)
			draw_cy_ctrls(data, obj, x, y);
		obj = obj->next;
		x += 100;
		if (x > 500)
		{
			x = 0;
			y += 100;
		}
	}
	sp_count = 0;
	return (0);
}