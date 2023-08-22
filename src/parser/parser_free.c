/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/21 18:58:03 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Free Sphere Object
void	free_sp(void *object)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)object;
	free(sphere->center);
	free(sphere);
}

// Free Plane Object
void	free_pl(void *object)
{
	t_plane	*plane;

	plane = (t_plane *)object;
	free(plane->normal_vec);
	free(plane->point);
	free(plane);
}

// Free Cylinder Object
void	free_cy(void *object)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)object;
	free(cylinder->normal_vec);
	free(cylinder->center);
	free(cylinder);
}

// Object Deletion
void	free_objects(t_object *objects_head)
{
	t_object	*current;

	current = objects_head;
	while (current)
	{
		current = objects_head->next;
		if (objects_head->type == SPHERE)
			free_sp(objects_head);
		if (objects_head->type == PLANE)
			free_pl(objects_head);
		if (objects_head->type == CYLINDER)
			free_cy(objects_head);
	}
	free(current);
}

// Free A, C and L
void	free_acl(t_amb *ambient_light, t_camera *camera, t_light *light)
{
	free(ambient_light);
	free(camera);
	free(light);
}
