/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:50:47 by fcullen           #+#    #+#             */
/*   Updated: 2023/09/26 14:51:01 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	print_color(t_color color)
{
	printf("Color: R=%f, G=%f, B=%f\n", color.r, color.g, color.b);
}

void	print_v(t_v3 p)
{
	printf("Point: x=%f, y=%f, z=%f\n", p.x, p.y, p.z);
}

void	print_m(t_matrix4 matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
			printf("%f ", matrix.m[i][j++]);
		printf("\n");
		i++;
	}
}
