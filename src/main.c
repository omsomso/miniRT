/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:02:24 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/17 12:28:16 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	quit(t_mlx *mlx)
{
	mlx_destroy_window(mlx->ptr, mlx->win);
	free(mlx);
	exit(0);
}

int	handle_keypress(int key, t_data *data)
{
	if (key == KEY_ESC)
		quit(data->mlx);
	if (key == 124)
		data->camera->pos->x -= 0.2;
	if (key == 123)
		data->camera->pos->x += 0.2;
	if (key == 43)
		data->camera->pos->y -= 0.2;
	if (key == 47)
		data->camera->pos->y += 0.2;
	if (key == 126)
		data->camera->pos->z += 0.1;
	if (key == 125)
		data->camera->pos->z -= 0.1;
	generate_rays(data);
	// printf("%d\n", key);
	return (0);
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
}

void	start_loop(t_data *data)
{
	mlx_hook(data->mlx->win, EVENT_KEYPRESS, 0, &handle_keypress, data);
	mlx_hook(data->mlx->win, EVENT_DESTROY, 0, &quit, data->mlx);
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
	init_window(data);
	if (parser(argv[1], &data->objects, data))
		return (1);
	generate_rays(data);
	printf("%f\n", data->camera->pos->x);
	start_loop(data);
	free_data(data);
	return (0);
}
