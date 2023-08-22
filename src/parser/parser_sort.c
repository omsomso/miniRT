/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/22 18:38:59 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_object*	merge_sort(t_object* head)
{
    if (!head || !head->next) return head;

    t_object* a;
    t_object* b;
    front_back_split(head, &a, &b);

    a = merge_sort(a);
    b = merge_sort(b);

    return sorted_merge(a, b);
}

double	compute_distance(t_v3 origin, t_object *obj)
{
	t_v3 *object_point;

	switch (obj->type)
	{
	case SPHERE:
		object_point = ((t_sphere *)obj->object)->center;
		break;
	case PLANE:
		object_point = ((t_plane *)obj->object)->point;
		break;
	case CYLINDER:
		object_point = ((t_cylinder *)obj->object)->center;
		break;
	default:
		return INFINITY;
	}

	return distance_to_point(origin, *object_point);
}

void	sort_objects_by_distance(t_v3 origin, t_object **head)
{
	t_object *temp = *head;

	// Compute the distances for each object in the list
	while (temp)
	{
		temp->distance = compute_distance(origin, temp);
		temp = temp->next;
	}
	// Use merge sort to sort the list based on the computed distances
	*head = merge_sort(*head);
}

void	front_back_split(t_object* source, t_object** front_ref, t_object** back_ref)
{
	t_object* fast;
	t_object* slow;

	if (source == NULL || source->next == NULL)
	{
		*front_ref = source;
		*back_ref = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;

		while (fast != NULL)
		{
			fast = fast->next;
			if (fast)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front_ref = source;
		*back_ref = slow->next;
		slow->next = NULL;
	}
}

// Merge sort objects by distance
t_object*	sorted_merge(t_object* a, t_object* b)
{
	t_object* result = NULL;

	if (!a)
		return b;
	else if (!b)
		return a;

	// Pick the smaller distance and recur
	if (a->distance <= b->distance)
	{
		result = a;
		result->next = sorted_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge(a, b->next);
	}
	return result;
}
