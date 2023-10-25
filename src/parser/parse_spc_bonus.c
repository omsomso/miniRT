/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaphod <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/10/13 17:35:39 by zaphod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Sphere Parser
int	parse_sp(char **s, t_object **objects)
{
	t_sphere	*sphere;
	char		**split;

	if (check_sp(s))
		return (1);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (1);
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
	char		**split;

	if (check_pl(s))
		return (1);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (1);
	plane->pl_ang_offset.x = 0;
	plane->pl_ang_offset.y = 0;
	plane->pl_ang_offset.z = 0;
	split = ft_split(s[1], ',');
	plane->point = get_vec(split);
	split = ft_split(s[2], ',');
	plane->normal = get_vec(split);
	if (!plane->point || !plane->normal)
		return (1);
	split = ft_split(s[3], ',');
	get_color(&(plane->color), split);
	add_object(objects, plane, PLANE, s);
	return (0);
}

// Parses color and inits angle offset for the cylinder
void	set_cy_struct_additional(t_cylinder *cylinder, char **s)
{
	char	**split;

	split = ft_split(s[5], ',');
	get_color(&(cylinder->color), split);
	cylinder->cy_ang_offset.x = 0;
	cylinder->cy_ang_offset.y = 0;
	cylinder->cy_ang_offset.z = 0;
}

// Init some cylinder values
void	initialize_cylinder(t_cylinder *cylinder)
{
	cylinder->cap_offsets[0] = -cylinder->height / 2;
	cylinder->cap_offsets[1] = cylinder->height / 2;
}

// Cylinder Parser
int	parse_cy(char **s, t_object **objects)
{
	t_cylinder	*cylinder;
	char		**split;

	if (check_cy(s))
		return (1);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (1);
	split = ft_split(s[1], ',');
	cylinder->center = get_vec(split);
	split = ft_split(s[2], ',');
	cylinder->normal = get_vec(split);
	if (!cylinder->center || !cylinder->normal)
		return (1);
	cylinder->diameter = ft_atoi(s[3]);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->height = ft_atoi(s[4]);
	initialize_cylinder(cylinder);
	set_cy_struct_additional(cylinder, s);
	add_object(objects, cylinder, CYLINDER, s);
	return (0);
}
