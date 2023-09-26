/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:50:34 by fcullen           #+#    #+#             */
/*   Updated: 2023/09/26 15:32:26 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Adds two colors together
t_color	add_colors(t_color color1, t_color color2)
{
	t_color	result;

	result.r = color1.r + color2.r;
	result.g = color1.g + color2.g;
	result.b = color1.b + color2.b;
	return (result);
}

// Multiplies two colors
t_color	mult_col(t_color color1, t_color color2)
{
	t_color	result;

	result.r = color1.r * color2.r;
	result.g = color1.g * color2.g;
	result.b = color1.b * color2.b;
	return (result);
}

// Multiplies color by scalar
t_color	mult_cs(t_color color, float s)
{
	t_color	result;

	result.r = color.r * s;
	result.g = color.g * s;
	result.b = color.b * s;
	return (result);
}

// Mlx function to set pixel color
void	set_pixel_color(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= data->win_width
		|| y < 0 || y >= data->win_height)
		return ;
	dst = data->mlxdata->addr + (y * data->mlxdata->line_length
			+ x * (data->mlxdata->bits_per_pixel / 8));
	*(unsigned int *) dst = color ;
}

// Converts from tcolor to int
int	convert_tcolor_to_int(t_color color)
{
	int	intcolor;

	intcolor = 0;
	intcolor |= ((int)(color.r) & 0xFF) << 16;
	intcolor |= ((int)(color.g) & 0xFF) << 8;
	intcolor |= ((int)(color.b) & 0xFF);
	return (intcolor);
}
