/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/22 18:17:23 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Function gets colors from char array and frees array
int	get_color(t_color *color, char **s)
{
	int	i;

	i = 0;
	if (!s[0] || !s[1] || !s[2])
		return (1);
	color->r = ft_atoi(s[0]);
	color->g = ft_atoi(s[1]);
	color->b = ft_atoi(s[2]);
	ft_ptrfree(s);
	return (0);
}

// Function Returns Pointer to 3D Vector from char Array + Frees Array
t_v3	*get_vec(char **s)
{
	t_v3	*vector;

	if (!s[0] || !s[1] || !s[2])
		return (NULL);
	vector = malloc(sizeof(t_v3));
	if (!vector)
		return (NULL);
	vector->x = ft_atof(s[0]);
	vector->y = ft_atof(s[1]);
	vector->z = ft_atof(s[2]);
	ft_ptrfree(s);
	return (vector);
}
