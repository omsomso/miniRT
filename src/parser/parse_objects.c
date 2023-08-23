/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/23 02:07:53 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Sphere Parser
int	parse_sp(char **s, t_object **objects)
{
	t_sphere	*sphere;
	t_v3		*center;
	char		**split;

	fix_last_whitespace(s, 4);
	if (check_sp(s))
		return (1);
	sphere = malloc(sizeof(t_sphere));
	center = malloc(sizeof(t_v3));
	if (!sphere || !center)
		return (1);
	sphere->center = center;
	split = ft_split(s[1], ',');
	sphere->center = get_vec(split);
	if (!sphere->center)
		return (1);
	sphere->diameter = ft_atof(s[2]);
	sphere->radius = sphere->diameter / 2;
	split = ft_split(s[3], ',');
	get_color(&(sphere->color), split);
	add_object(objects, sphere, SPHERE, s);
	return (0);
}

// Plane Parser
int	parse_pl(char **s, t_object **objects)
{
	t_plane		*plane;
	t_v3		*point;
	t_v3		*normal_vec;
	char		**split;

	fix_last_whitespace(s, 4);
	if (check_pl(s))
		return (1);
	plane = malloc(sizeof(t_plane));
	point = malloc(sizeof(t_v3));
	normal_vec = malloc(sizeof(t_v3));
	if (!plane || !point || !normal_vec)
		return (1);
	split = ft_split(s[1], ',');
	plane->point = get_vec(split);
	split = ft_split(s[2], ',');
	plane->normal_vec = get_vec(split);
	if (!plane->point || !plane->normal_vec)
		return (1);
	split = ft_split(s[3], ',');
	get_color(&(plane->color), split);
	add_object(objects, plane, PLANE, s);
	return (0);
}

// Cylinder Parser
int	parse_cy(char **s, t_object **objects)
{
	t_cylinder	*cylinder;
	t_v3		*center;
	t_v3		*normal_vec;
	char		**split;

	if (check_cy(s))
		return (1);
	cylinder = malloc(sizeof(t_cylinder));
	center = malloc(sizeof(t_v3));
	normal_vec = malloc(sizeof(t_v3));
	if (!cylinder || !center || !normal_vec)
		return (1);
	split = ft_split(s[1], ',');
	cylinder->center = get_vec(split);
	split = ft_split(s[2], ',');
	cylinder->normal_vec = get_vec(split);
	if (!cylinder->center || !cylinder->normal_vec)
		return (1);
	cylinder->diameter = ft_atoi(s[3]);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->height = ft_atoi(s[4]);
	split = ft_split(s[5], ',');
	get_color(&(cylinder->color), split);
	add_object(objects, cylinder, CYLINDER, s);
	return (0);
}

// Inits new object
t_object	*create_obj(void *object, t_type type, char **s)
{
	t_object	*new_object;

	new_object = malloc(sizeof(t_object));
	if (!new_object)
		return (NULL);
	new_object->object = object;
	new_object->type = type;
	new_object->ambient_coefficient = 0.2;
	new_object->diffuse_coefficient = 0.9;
	new_object->next = NULL;
	new_object->distance = INFINITY;
	new_object->mirror = false;
	if (!s[4])
	{
		new_object->check = false;
		new_object->mirror = false;
	}
	return (new_object);
}

// Object Creation
void	add_object(t_object **obj_head, void *object, t_type type, char **s)
{
	t_object	*current;
	t_object	*new_object;

	new_object = create_obj(object, type, s);
	if (!new_object)
		return ;
	if (s[4] && ft_atoi(s[4]) == 1)
	{
		new_object->check = true;
		if (s[5] && ft_atoi(s[5]) == 1)
				new_object->mirror = true;
	}
	if (*obj_head == NULL)
			*obj_head = new_object;
	else
	{
		current = *obj_head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_object;
	}
}
