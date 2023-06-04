/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:02:24 by kpawlows          #+#    #+#             */
/*   Updated: 2023/06/04 20:47:54 by kpawlows         ###   ########.fr       */
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

void	init_window(t_data *data)
{
	data->mlx->mlx = mlx_init();
	data->mlx->win = mlx_new_window(data->mlx->mlx, data->win_width, data->win_height, "miniRT");
}

void	start_loop(t_data *data)
{
	mlx_hook(data->mlx->win, EVENT_KEYPRESS, 0, &handle_keypress, data->mlx);
	mlx_hook(data->mlx->win, EVENT_DESTROY, 0, &quit, data->mlx);
	mlx_loop(data->mlx->mlx);
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
	start_loop(data);
	free_data(data);
	return (0);
}
