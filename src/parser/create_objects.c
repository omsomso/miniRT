/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/10/07 14:09:42 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Inits new object
t_object	*create_obj(void *object, t_type type, char **s)
{
	t_object	*new_object;

	(void) s;
	new_object = malloc(sizeof(t_object));
	if (!new_object)
		return (NULL);
	new_object->object = object;
	new_object->type = type;
	new_object->ambient_coefficient = 0.2;
	new_object->diffuse_coefficient = 0.9;
	new_object->next = NULL;
	new_object->distance = INFINITY;
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
