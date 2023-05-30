/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:31:12 by fcullen           #+#    #+#             */
/*   Updated: 2023/05/30 20:28:31 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Function To Get Colors
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
// Function Returns 3D Vector from char Array + Frees Array
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

// Ambient Light Parser
int	parse_a(char **s, t_data **data)
{
	t_amb	*ambient_light;
	char	**colors;

	ambient_light = malloc(sizeof(t_amb));
	if (!ambient_light || !s[1] || !s[2])
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
	char		**split_pos;
	char		**split_normals;

	camera = malloc(sizeof(t_camera));
	if (!camera || !s[1] || !s[2] || !s[3])
		return (1);
	split_pos = ft_split(s[1], ',');
	camera->pos = get_vec(split_pos);
	split_normals = ft_split(s[2], ',');
	camera->normal_vec = get_vec(split_normals);
	camera->fov = ft_atoi(s[3]);
	(*data)->camera = camera;
	return (0);
}

// Light Parser
int	parse_l(char **s, t_data **data)
{
	t_light	*light;
	char	**split_pos;
	char	**split_color;

	light = malloc(sizeof(t_light));
	if (!light || !s[1] || !s[2] || !s[3])
		return (1);
	split_pos = ft_split(s[1], ',');
	printf("%s\n", split_pos[0]);
	light->pos = get_vec(split_pos);
	if (!light->pos)
		return (1);
	light->brightness = ft_atoi(s[2]);
	split_color = ft_split(s[3], ',');
	get_color(&(light->color), split_color);
	(*data)->light = light;
	return (0);
}

// Sphere Parser
int	parse_sp(char **s, t_object **objects)
{
	t_sphere	*sphere;
	t_v3		*center;
	char		**split;
	t_object	*new_object;

	(void)objects;
	sphere = malloc(sizeof(t_sphere));
	center = malloc(sizeof(t_v3));
	new_object = malloc(sizeof(t_object));
	if (!sphere || !center || !new_object)
		return (1);
	sphere->center = center;
	split = ft_split(s[1], ',');
	sphere->center = get_vec(split);
	if (!sphere->center)
		return (1);
	sphere->diameter = ft_atof(s[2]);
	split = ft_split(s[3], ',');
	get_color(&(sphere->color), split);
	return (0);
}

// Plane Parser
int	parse_pl(char **s, t_object **objects)
{
	t_plane		*plane;
	t_v3		*point;
	t_v3		*normal_vec;
	char		**split;

	(void)objects;
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
	return (0);
}

// Cylinder Parser
int	parse_cy(char **s, t_object **objects)
{
	t_cylinder	*cylinder;
	t_v3		*center;
	t_v3		*normal_vec;
	char		**split;

	(void)objects;
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
	cylinder->height = ft_atoi(s[4]);
	split = ft_split(s[5], ',');
	get_color(&(cylinder->color), split);
	return (0);
}


// Line Parser Function
int	parse_line(char *line, t_object *objects, t_data *data)
{
	char	**split;
	int		obj_count;

	split = ft_split(line, ' ');
	obj_count = 0;
	(void)objects;
	if (!split[0])
		return (ft_ptrfree(split), -1);
	if (!ft_strncmp("A", split[0], ft_strlen(split[0])))
	{
		if (parse_a(split, &data))
			return (ft_ptrfree(split), 1);
	}
	else if (!ft_strncmp("C", split[0], ft_strlen(split[0])))
	{
		if (parse_c(split, &data))
			return (ft_ptrfree(split), 1);
	}
	else if (!ft_strncmp("L", split[0], ft_strlen(split[0])))
	{
		if (parse_l(split, &data))
			return (ft_ptrfree(split), 1);
	}
	else if (!ft_strncmp("sp", split[0], ft_strlen(split[0])))
	{
		if (parse_sp(split, &objects))
			return (ft_ptrfree(split), 1);
	}
	else if (!ft_strncmp("pl", split[0], ft_strlen(split[0])))
	{
		if (parse_pl(split, &objects))
			return (ft_ptrfree(split), 1);
	}
	else if (!ft_strncmp("cy", split[0], ft_strlen(split[0])))
	{
		if (parse_cy(split, &objects))
			return (ft_ptrfree(split), 1);
	}
	return (0);
}

// Main Parser Function
// needs check for A, C, L duplicates
int	parser(char *filename, t_object *objects, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (fd);
	line = get_next_line(fd);
	if (!line)
	{
		write(1, "Scene file empty\n", 17);
		return (-1);
	}
	while (line)
	{
		printf("%s\n", line);
		parse_line(line, objects, data);
		line = get_next_line(fd);
	}
	printf("%f\n", data->light->pos->x);
	return (0);
}
