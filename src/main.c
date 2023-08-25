/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:02:24 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/26 01:25:08 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	free_data(t_data *data)
{
	free_objects(data->objects);
	free_acl(data->ambient_light, data->camera, data->light);
}

int	quit(t_mlx *mlx)
{
	mlx_destroy_window(mlx->ptr, mlx->win);
	mlx_destroy_window(mlx->ptr, mlx->win_gui);
	mlx_destroy_image(mlx->ptr, mlx->bckg);
	// mlx_destroy_image(mlx->ptr, mlx->sphere);
	free(mlx);
	exit(0);
}

// Rotate the camera's orientation vector around the up vector (y-axis) by the given angle in degrees
void rotate_camera(t_camera *camera, double angle_deg)
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

void rotate_camera_x(t_camera *camera, double angle_deg)
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

int handle_keypress(int key, t_data *data)
{
	if (key == KEY_ESC)
		quit(data->mlx);
	if (key == KEY_LEFT)
	{
		rotate_camera(data->camera, 5.0);
		generate_rays(data);
	}
	else if (key == KEY_RIGHT)
	{
		rotate_camera(data->camera, -5.0);
		generate_rays(data);
	}
	else if (key == KEY_UP)
	{
		rotate_camera_x(data->camera, 5.0);
		generate_rays(data);
	}
	else if (key == KEY_DOWN)
	{
		rotate_camera_x(data->camera, -5.0);
		generate_rays(data);
	}
	
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
	generate_rays(data);
	// printf("%d\n", key);
	return (0);
}

void	init_window(t_data *data)
{
	int	x;
	int	y;
	int	obj_count;

	data->mlx->ptr = mlx_init();
	obj_count = count_objects(data->objects);
	data->mlx->win_gui = mlx_new_window(data->mlx->ptr, obj_count * 100, calculate_gui_height(obj_count), "miniRT Object Controls");
	data->mlx->bckg = mlx_xpm_file_to_image(data->mlx->ptr, "assets/bckg.xpm", &x, &y);
	data->mlx->sel = mlx_xpm_file_to_image(data->mlx->ptr, "assets/select.xpm", &x, &y);
	data->mlx->win = mlx_new_window(data->mlx->ptr, data->win_width, data->win_height, "miniRT");
	draw_gui(data, 1);
	data->mlxdata = malloc(sizeof(t_mlxdata));
	if (!data->mlxdata)
		return ;
	data->mlxdata->img = mlx_new_image(data->mlx->ptr, 1080, 720);
	data->mlxdata->addr = mlx_get_data_addr(data->mlxdata->img,
			&data->mlxdata->bits_per_pixel, &data->mlxdata->line_length,
			&data->mlxdata->endian);
}

void	start_loop(t_data *data)
{
	mlx_hook(data->mlx->win, EVENT_KEYPRESS, 0, &handle_keypress, data);
	mlx_hook(data->mlx->win, EVENT_DESTROY, 0, &quit, data->mlx);
	mlx_mouse_hook(data->mlx->win_gui, &handle_mouse, data);
	mlx_loop(data->mlx->ptr);
}

t_data	*init_data(void)
{
	t_data	*data;
	t_mlx	*mlx;

	data = malloc(sizeof(t_data));
	mlx = malloc(sizeof(t_mlx));
	if (!data)
		return (NULL);
	data->mlx = malloc(sizeof(t_mlx));
	if (!data->mlx)
		return (NULL);
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	data->objects = malloc(sizeof(t_object));
	if (!data->objects)
		return (NULL);
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
	printf("%f\n", data->camera->pos->x);
	start_loop(data);
	free_data(data);
	return (0);
}
