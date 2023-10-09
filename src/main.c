/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:02:24 by kpawlows          #+#    #+#             */
/*   Updated: 2023/10/10 00:05:02 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	free_data(t_data *data)
{
	free_objects(data->objects);
	free_acl(data->ambient_light, data->camera, data->light);
	free(data->pics);
	free(data->mlxdata);
	free(data->mlx);
	free(data);
}

int	quit(t_data *data)
{
	mlx_clear_window(data->mlx->ptr, data->mlx->win);
	mlx_clear_window(data->mlx->ptr, data->mlx->win_gui);
	mlx_destroy_image(data->mlx->ptr, data->pics->bckg);
	mlx_destroy_image(data->mlx->ptr, data->pics->sel);
	mlx_destroy_image(data->mlx->ptr, data->pics->sel_p);
	mlx_destroy_image(data->mlx->ptr, data->pics->empty);
	mlx_destroy_window(data->mlx->ptr, data->mlx->win);
	mlx_destroy_window(data->mlx->ptr, data->mlx->win_gui);
	free(data->gui);
	free_data(data);
	exit(0);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	data->objects = malloc(sizeof(t_object));
	if (!data->objects)
		return (NULL);
	data->auto_retrace = 0;
	return (data);
}

int	check_main_args(int argc, char **argv)
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

	if (check_main_args(argc, argv))
		return (1);
	data = init_data();
	if (!data)
		return (1);
	if (parser(argv[1], &data->objects, data))
		return (1);
	init_window(data);
	generate_rays(data);
	start_loop(data);
	return (0);
}
