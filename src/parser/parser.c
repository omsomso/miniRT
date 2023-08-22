/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:31:12 by fcullen           #+#    #+#             */
/*   Updated: 2023/08/22 19:04:27 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Object Creation
void	add_object(t_object **objects_head, void *object, t_type type, char **s)
{
	t_object	*current;
	t_object	*new_object;

	new_object = malloc(sizeof(t_object));
	if (!new_object)
		return ;
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
	else if (s[4] && ft_atoi(s[4]) == 1)
	{
		new_object->check = true;
		if (s[5] && ft_atoi(s[5]) == 1)
				new_object->mirror = true;
	}

	if (*objects_head == NULL)
			*objects_head = new_object;
	else
	{
		current = *objects_head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_object;
	}
}

int	parse_acl(char **s, t_data *data)
{
	if (!ft_strncmp("A", s[0], ft_strlen(s[0])))
	{
		if (parse_a(s, &data))
			return (ft_ptrfree(s), 1);
	}
	else if (!ft_strncmp("C", s[0], ft_strlen(s[0])))
	{
		if (parse_c(s, &data))
			return (ft_ptrfree(s), 1);
	}
	else if (!ft_strncmp("L", s[0], ft_strlen(s[0])))
	{
		if (parse_l(s, &data))
			return (ft_ptrfree(s), 1);
	}
}

// Parse Sphere, Plane and Cylinder
int	parse_spc(char **s, t_object **objects)
{
	if (!ft_strncmp("sp", s[0], ft_strlen(s[0])))
	{
		if (parse_sp(s, objects))
			return (1);
	}
	else if (!ft_strncmp("pl", s[0], ft_strlen(s[0])))
	{
		if (parse_pl(s, objects))
			return (1);
	}
	else if (!ft_strncmp("cy", s[0], ft_strlen(s[0])))
	{
		if (parse_cy(s, objects))
			return (1);
	}
	return (0);
}

// Line Parser Function
int	parse_line(char *line, t_object **objects, t_data *data)
{
	char	**split;
	int		obj_count;

	split = ft_split(line, ' ');
	obj_count = 0;
	if (!split[0])
		return (ft_ptrfree(split), -1);
	if (check_line(line, split[0]))
	{
		write(2, "Error: Invalid identifier : ", 28);
		ft_putendl_fd(split[0], 2);
		return (ft_ptrfree(split), 1);
	}
	if (parse_spc(split, objects) || parse_acl(split, data))
		return (ft_ptrfree(split), 1);
	return (0);
}

int	parse_loop(int fd, t_object **objects, t_data *data)
{
	char	*line;

	line = get_next_line(fd);
	*objects = NULL;
	if (!line)
	{
		write(1, "Scene file empty\n", 17);
		return (1);
	}
	while (line)
	{
		// printf("line = %s\n", line);
		line = line_fixspace(line);
		if (parse_line(line, objects, data))
		{
			write(1, "Parsing error\n", 14);
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

// Main Parser Function
// needs check for A, C, L duplicates
int	parser(char *filename, t_object **objects, t_data *data)
{
	int		fd;

	init_scene(data);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (fd);
	if (parse_loop(fd, objects, data))
		return (-1);
	if (check_scene(data))
		return (-1);
	sort_objects_by_distance(*data->camera->pos, &(*objects));
	dbg_parser(data);
	return (0);
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