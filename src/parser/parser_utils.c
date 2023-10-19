/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/09/26 15:07:40 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Function gets colors from char array and frees array
int	get_color(t_color *color, char **s)
{
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

double	compute_distance(t_v3 origin, t_object *obj)
{
	t_v3	*object_point;

	if (obj->type == SPHERE)
		object_point = ((t_sphere *)obj->object)->center;
	else if (obj->type == PLANE)
		object_point = ((t_plane *)obj->object)->point;
	else if (obj->type == CYLINDER)
		object_point = ((t_cylinder *)obj->object)->center;
	else
		return (INFINITY);
	return (distance_to_point(origin, *object_point));
}

// If last string in s is a newline, frees and NULLs it
void	fix_last_whitespace(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (i > 1 && s[i - 1][0] && s[i - 1][0] == '\n')
	{
		free(s[i - 1]);
		s[i - 1] = NULL;
	}
}

t_v3	*normalize_ptr(t_v3	*a)
{
	double	length;

	length = sqrt((*a).x * (*a).x + (*a).y
			* (*a).y + (*a).z * (*a).z);
	if (length != 0.0)
	{
		(*a).x /= length;
		(*a).y /= length;
		(*a).z /= length;
	}
	return (a);
}
