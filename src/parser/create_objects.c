/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/09/01 19:56:23 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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
	new_object->mirror = 0;
	if (!s[4])
	{
		new_object->check = 0;
		new_object->mirror = 0;
	}
	return (new_object);
}

void	add_object_additional(t_object *new_object, t_type type, char **s)
{
	if (s[4] && ft_atoi(s[4]) == 1)
	{
		new_object->check = 1;
		if (s[5] && ft_atoi(s[5]) == 1)
				new_object->mirror = 1;
	}
	else if (type == SPHERE && s[4])
	{
		if (ft_atoi(s[4]) == 1)
			new_object->check = 1;
		if (s[5] && ft_atoi(s[5]) == 1)
			new_object->mirror = 1;
	}
	else if (type == CYLINDER && s[6])
	{
		if (ft_atoi(s[6]) == 1)
			new_object->check = 1;
		if (s[7] && ft_atoi(s[7]) == 1)
			new_object->mirror = 1;
	}
}

// Object Creation
void	add_object(t_object **obj_head, void *object, t_type type, char **s)
{
	t_object	*current;
	t_object	*new_object;

	new_object = create_obj(object, type, s);
	if (!new_object)
		return ;
	add_object_additional(new_object, type, s);
	if (!s[4])
	{
		new_object->check = 0;
		new_object->mirror = 0;
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
