/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:40:20 by fcullen           #+#    #+#             */
/*   Updated: 2023/05/30 09:55:23 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This is a better version of the mlx_pixel_put function.
// void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
// {
// 	char	*dst;

// 	if (x < 0 || x >= data->win_width
// 		|| y < 0 || y >= data->win_height)
// 		return ;
// 	dst = fdf->mlxdata->addr + (y * fdf->mlxdata->line_length
// 			+ x * (fdf->mlxdata->bits_per_pixel / 8));
// 	*(unsigned int *) dst = color ;
// }

// // Check if pixel is within the screen limits
// int	pixl_check(t_v3d v)
// {
// 	if (v.coord[X] > data->win_width || v.coord[X] < 0)
// 		return (0);
// 	if (v.coord[Y] > data->win_height || v.coord[Y] < 0)
// 		return (0);
// 	return (1);
// }