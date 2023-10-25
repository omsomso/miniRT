/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:02:44 by zaphod           #+#    #+#             */
/*   Updated: 2023/10/10 00:04:20 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

char	*ft_ftoa(float f)
{
	char	*tmp1;
	char	*tmp2;
	int		dec;

	tmp1 = ft_itoa((int)f);
	tmp1 = ft_strjoin_ff(tmp1, ".");
	dec = (f - (int)f) * 100;
	if (dec < 0)
		dec *= -1;
	tmp2 = ft_itoa(dec);
	return (ft_strjoin_fb(tmp1, tmp2));
}

int	cut_values_int(int *a, int max_a, int min_a)
{
	if (*a > max_a)
		*a = max_a;
	if (*a < min_a)
		*a = min_a;
	return (*a);
}

float	cut_values(float *a, float max_a, float min_a)
{
	if (*a > max_a)
		*a = max_a;
	if (*a < min_a)
		*a = min_a;
	return (*a);
}

// Maps the x, y, and z components of the normal to the RGB values
// to visualize normals
t_color	visualize_normals(t_int *intersection)
{
	t_color	color;
	t_v3	normal;

	normal = normalize(intersection->normal);
	color.r = (unsigned char)((normal.x + 1.0) * 127.5);
	color.g = (unsigned char)((normal.y + 1.0) * 127.5);
	color.b = (unsigned char)((normal.z + 1.0) * 127.5);
	return (color);
}

void	free_camera_basis(t_data *data)
{
	if (data->camera->right)
		free(data->camera->right);
	if (data->camera->up)
		free(data->camera->up);
}
