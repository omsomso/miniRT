/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_acl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/09/26 13:19:47 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Ambient Light Parser
int	parse_a(char **s, t_data **data)
{
	t_amb	*ambient_light;
	char	**colors;

	if (check_a(s))
		return (1);
	ambient_light = malloc(sizeof(t_amb));
	if (!ambient_light)
		return (1);
	ambient_light->ratio = ft_atof(s[1]);
	colors = ft_split(s[2], ',');
	get_color(&(ambient_light->color), colors);
	(*data)->ambient_light = ambient_light;
	ft_ptrfree(s);
	return (0);
}

// Camera Parser
int	parse_c(char **s, t_data **data)
{
	t_camera	*camera;
	char		**split;

	if (check_c(s))
		return (1);
	camera = malloc(sizeof(t_camera));
	if (!camera || !s[1] || !s[2] || !s[3])
		return (1);
	split = ft_split(s[1], ',');
	camera->pos = get_vec(split);
	split = ft_split(s[2], ',');
	camera->normal = get_vec(split);
	camera->fov = ft_atoi(s[3]);
	(*data)->camera = camera;
	ft_ptrfree(s);
	return (0);
}

// Light Parser
int	parse_l(char **s, t_data **data)
{
	t_light	*light;
	char	**split;

	if (check_l(s))
		return (1);
	light = malloc(sizeof(t_light));
	if (!light || !s[1] || !s[2])
		return (1);
	split = ft_split(s[1], ',');
	light->pos = get_vec(split);
	if (!light->pos)
		return (1);
	light->brightness = ft_atof(s[2]);
	split = ft_split(s[3], ',');
	get_color(&(light->color), split);
	(*data)->light = light;
	ft_ptrfree(s);
	return (0);
}
