/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/22 20:58:37 by kpawlows         ###   ########.fr       */
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

void	dbg_parser(t_data *data)
{
	printf("Parsing Done!\n");
	printf("The camera center's coordinates are: %f, %f, %f\n", data->camera->pos->x, data->camera->pos->y, data->camera->pos->z);
	printf("The camera orientation is: %f, %f, %f\n", data->camera->normal_vec->x, data->camera->normal_vec->y, data->camera->normal_vec->z);
	t_object *obj = data->objects;
	while (obj != NULL)
	{
		if (obj->type == SPHERE)
		{
			t_sphere *sphere = (t_sphere*)obj->object;
			printf("The sphere center's coordinates are: %f, %f, %f\n", sphere->center->x, sphere->center->y, sphere->center->z);
			// printf("Diameter = %f\n", sphere->diameter);
			// printf("Sphere color.r = %f\n", sphere->color.r);
		}
		else if (obj->type == PLANE)
		{
			t_sphere *plane = (t_sphere*)obj->object;
			printf("The plane's coordinates are: %f, %f, %f\n", plane->center->x, plane->center->y, plane->center->z);
			// printf("Diameter = %f\n", sphere->diameter);
			// printf("Sphere color.r = %f\n", sphere->color.r);
		}
		obj = obj->next;
	}
}
