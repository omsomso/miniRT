/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:02:24 by kpawlows          #+#    #+#             */
/*   Updated: 2023/05/31 09:50:04 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	quit(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx);
	exit(0);
}

int	handle_keypress(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
		quit(mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	*mlx;
	t_data	*data;

	if (argc < 2)
	{
		write(1, "Please provide a scene file (.rt).\n", 35);
		return (0);
	}
	mlx = malloc(sizeof(t_mlx));
	data = malloc(sizeof(t_data));
	data->objects = malloc(sizeof(t_object));
	if (!data->objects)
		return (1);
	data->objects = NULL;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, 500, 500, "test");
	parser(argv[1], &data->objects, data);
	mlx_hook(mlx->win, EVENT_KEYPRESS, 0, &handle_keypress, mlx);
	mlx_hook(mlx->win, EVENT_DESTROY, 0, &quit, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
