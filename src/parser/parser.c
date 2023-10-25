/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:31:12 by zaphod           #+#    #+#             */
/*   Updated: 2023/10/24 14:53:30 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Parse Ambient Light, Camera and Light
int	parse_acl(char **s, t_data *data)
{
	if (!ft_strncmp("A", s[0], ft_strlen(s[0])))
	{
		if (parse_a(s, &data))
			return (1);
	}
	else if (!ft_strncmp("C", s[0], ft_strlen(s[0])))
	{
		if (parse_c(s, &data))
			return (1);
	}
	else if (!ft_strncmp("L", s[0], ft_strlen(s[0])))
	{
		if (parse_l(s, &data))
			return (1);
	}
	return (0);
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

	split = NULL;
	split = ft_split(line, ' ');
	if (!split || !split[0])
		return (ft_ptrfree(split), 1);
	fix_last_whitespace(split);
	// printf("yo\n");
	// printf("lne :")
	if (check_line(line, split[0]))
	{
		write(2, "Error\nInvalid identifier : ", 28);
		ft_putendl_fd(split[0], 2);
		return (ft_ptrfree(split), 1);
	}
	else if (parse_spc(split, objects) || parse_acl(split, data))
		return (ft_ptrfree(split), 1);
	ft_ptrfree(split);
	return (0);
}

// Main Parser Loop
int	parse_loop(int fd, t_object **objects, t_data *data)
{
	char	*line;

	line = get_next_line(fd);
	free(*objects);
	*objects = NULL;
	if (!line)
	{
		write(2, "Error\nScene file empty\n", 23);
		return (1);
	}
	while (line)
	{
		line = line_fixspace(line);
		if (parse_line(line, objects, data))
		{
			write(2, "Error\nParsing error\n", 20);
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

// Main Parser Function
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
	sort_objects_by_distance(*data->camera->pos, objects);
	return (0);
}
