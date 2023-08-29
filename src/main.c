/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:02:24 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/29 18:21:15 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	free_data(t_data *data)
{
	free_objects(data->objects);
	free_acl(data->ambient_light, data->camera, data->light);
}

int	quit(t_data *data)
{
	mlx_clear_window(data->mlx->ptr, data->mlx->win);
	mlx_clear_window(data->mlx->ptr, data->mlx->win_gui);
	mlx_destroy_image(data->mlx->ptr, data->pics->bckg);
	mlx_destroy_image(data->mlx->ptr, data->pics->sel);
	mlx_destroy_image(data->mlx->ptr, data->pics->sel_p);
	mlx_destroy_window(data->mlx->ptr, data->mlx->win);
	mlx_destroy_window(data->mlx->ptr, data->mlx->win_gui);
	free(data->mlx);
	// free(data->gui);
	exit(0);
}

int handle_keypress(int key, t_data *data)
{
	if (key == KEY_ESC)
		quit(data);
	if (key == KEY_LEFT)
		rotate_camera_y(data->camera, 5.0);
	else if (key == KEY_RIGHT)
		rotate_camera_y(data->camera, -5.0);
	else if (key == KEY_UP)
		rotate_camera_x(data->camera, 5.0);
	else if (key == KEY_DOWN)
		rotate_camera_x(data->camera, -5.0);

	// Handle other keypresses here
	if (key == KEY_A)
		data->camera->pos->x += 0.2;
	if (key == KEY_D)
		data->camera->pos->x -= 0.2;
	if (key == KEY_E)
		data->camera->pos->y -= 0.2;
	if (key == KEY_Q)
		data->camera->pos->y += 0.2;
	if (key == KEY_W)
		data->camera->pos->z -= 0.1;
	if (key == KEY_S)
		data->camera->pos->z += 0.1;
	if (key == KEY_ENTER && data->auto_retrace == 0)
		data->auto_retrace = 1;
	else if (key == KEY_ENTER && data->auto_retrace == 1)
		data->auto_retrace = 0;
	conditional_retrace(data, 0);
	return (0);
}

void	init_gui_window(t_data *data, t_mlx *m, int x, int y)
{
	t_pics	*pics;
	t_pos	pos;
	int		obj_count;
	t_gui	*gui;

	pics = malloc(sizeof(t_pics));
	if (!pics)
		return ;
	m = data->mlx;
	pos.x = 0;
	pos.y = 0;
	pics->bckg = mlx_xpm_file_to_image(m->ptr, "assets/bckg.xpm", &x, &y);
	pics->sel = mlx_xpm_file_to_image(m->ptr, "assets/select.xpm", &x, &y);
	pics->sel_p = mlx_xpm_file_to_image(m->ptr, "assets/sel_p.xpm", &x, &y);
	printf("Mouse wheel\t: modify parameters\nRight click\t: retrace\n");
	printf("Enter\t\t: toggle auto retrace\n");
	data->pics = pics;
	obj_count = count_objects(data->objects);
	m->win_gui = mlx_new_window(m->ptr, calculate_gui_width(obj_count), \
	calculate_gui_height(obj_count), "miniRT Object Controls");
	gui = init_gui_struct(data);
	draw_gui(data, gui);
}

void	init_window(t_data *data)
{
	data->mlx->ptr = mlx_init();
	data->mlx->win = mlx_new_window(data->mlx->ptr, data->win_width, data->win_height, "miniRT");
	data->mlxdata = malloc(sizeof(t_mlxdata));
	if (!data->mlxdata)
		return ;
	data->mlxdata->img = mlx_new_image(data->mlx->ptr, 1080, 720);
	data->mlxdata->addr = mlx_get_data_addr(data->mlxdata->img,
			&data->mlxdata->bits_per_pixel, &data->mlxdata->line_length,
			&data->mlxdata->endian);
	init_gui_window(data, data->mlx, 0, 0);
}

void	start_loop(t_data *data)
{
	mlx_hook(data->mlx->win, EVENT_KEYPRESS, 0, &handle_keypress, data);
	mlx_hook(data->mlx->win, EVENT_DESTROY, 0, &quit, data);
	mlx_mouse_hook(data->mlx->win, &handle_mouse, data);
	mlx_hook(data->mlx->win_gui, EVENT_KEYPRESS, 0, &handle_keypress, data);
	mlx_hook(data->mlx->win_gui, EVENT_DESTROY, 0, &quit, data);
	mlx_mouse_hook(data->mlx->win_gui, &handle_mouse, data);
	mlx_loop(data->mlx->ptr);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->mlx = malloc(sizeof(t_mlx));
	if (!data->mlx)
		return (NULL);
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	data->objects = malloc(sizeof(t_object));
	if (!data->objects)
		return (NULL);
	data->auto_retrace = 0;
	return (data);
}

int	check_args(int argc, char **argv)
{
	if (argc < 2)
	{
		write(1, "Please provide a scene file (.rt).\n", 35);
		return (1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt", 3))
	{
		write(1, "Please provide a scene file (.rt).\n", 35);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (check_args(argc, argv))
		return (1);
	data = init_data();
	if (!data)
		return (1);
	if (parser(argv[1], &data->objects, data))
		return (1);
	init_window(data);
	generate_rays(data);
	// printf("%f\n", data->camera->pos->x);
	start_loop(data);
	free_data(data);
	return (0);
}
