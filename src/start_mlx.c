/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:42:18 by kpawlows          #+#    #+#             */
/*   Updated: 2023/10/09 23:05:43 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	init_gui_window(t_data *data, t_mlx *m, int x, int y)
{
	t_pics	*pics;
	t_pos	pos;
	int		obj_count;
	t_gui	*gui;

	pics = malloc(sizeof(t_pics));
	if (!pics)
		return ;
	pos.x = 0;
	pos.y = 0;
	pics->bckg = mlx_xpm_file_to_image(m->ptr, "assets/bckg.xpm", &x, &y);
	pics->sel = mlx_xpm_file_to_image(m->ptr, "assets/select.xpm", &x, &y);
	pics->sel_p = mlx_xpm_file_to_image(m->ptr, "assets/sel_p.xpm", &x, &y);
	pics->empty = mlx_xpm_file_to_image(m->ptr, "assets/empty.xpm", &x, &y);
	printf("Mouse wheel\t: modify parameters\nRight click\t: retrace\n");
	printf("Enter\t\t: toggle auto retrace\n");
	data->pics = pics;
	obj_count = count_objects(data->objects);
	m->win_gui = mlx_new_window(m->ptr, compute_gui_width(obj_count), \
	compute_gui_height(obj_count), "miniRT Object Controls");
	gui = init_gui_struct(data);
	draw_gui(data, gui);
}

void	init_window(t_data *data)
{
	t_mlx	*m;

	m = malloc(sizeof(t_mlx));
	if (!m)
		return ;
	m->ptr = mlx_init();
	m->win = mlx_new_window(m->ptr, data->win_width, \
	data->win_height, "miniRT");
	data->mlxdata = malloc(sizeof(t_mlxdata));
	if (!data->mlxdata)
		return ;
	data->mlxdata->img = mlx_new_image(m->ptr, 1080, 720);
	data->mlxdata->addr = mlx_get_data_addr(data->mlxdata->img,
			&data->mlxdata->bits_per_pixel, &data->mlxdata->line_length,
			&data->mlxdata->endian);
	data->mlx = m;
	init_gui_window(data, data->mlx, 0, 0);
}

void	start_loop(t_data *data)
{
	mlx_hook(data->mlx->win, EVENT_KEYPRESS, 0, &handle_keypress, data);
	mlx_hook(data->mlx->win, EVENT_DESTROY, 0, &quit, data);
	mlx_mouse_hook(data->mlx->win_gui, &handle_mouse_gui, data);
	mlx_mouse_hook(data->mlx->win, &handle_mouse, data);
	mlx_hook(data->mlx->win_gui, EVENT_KEYPRESS, 0, &handle_keypress, data);
	mlx_hook(data->mlx->win_gui, EVENT_DESTROY, 0, &quit, data);
	mlx_loop(data->mlx->ptr);
}
