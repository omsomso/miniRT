/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/10/09 23:59:44 by kpawlows         ###   ########.fr       */
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
	free(plane->normal);
	free(plane->point);
	free(plane);
}

// Free Cylinder Object
void	free_cy(void *object)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)object;
	free(cylinder->normal);
	free(cylinder->center);
	free(cylinder);
}

// Object Deletion
void	free_objects(t_object *objects_head)
{
	t_object	*current;
	t_object	*tofree;

	current = objects_head;
	while (current)
	{
		if (current->type == SPHERE)
			free_sp(current->object);
		if (current->type == PLANE)
			free_pl(current->object);
		if (current->type == CYLINDER)
			free_cy(current->object);
		tofree = current;
		current = current->next;
		free(tofree);
	}
	free(current);
}

// Free A, C and L
void	free_acl(t_amb *ambient_light, t_camera *camera, t_light *light)
{
	free(ambient_light);
	free(camera->normal);
	free(camera->up);
	free(camera->pos);
	free(camera);
	free(light->pos);
	free(light);
}
