/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:31:12 by fcullen           #+#    #+#             */
/*   Updated: 2023/05/27 18:32:12 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Ambient Light Parser
int	parse_a(char **s, t_object *objects)
{
	return (0);
}

// Line Parser Function
int	parse_line(char *line, t_object *objects)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split[0])
		return (ft_ptrfree(split), -1);
	else if (!ft_strncmp("A", split[0], ft_strlen(split[0])))
		if (parse_a(split, objects))
			return (ft_ptrfree(split), 1);
	// else if (!ft_strncmp("C", split[0], ft_strlen(split[0])))
	// 	if (parse_c(split, objects))
	// 		return (ft_ptrfree(split), 1);
	// else if (!ft_strncmp("L", split[0], ft_strlen(split[0])))
	// 	if (parse_l())
	// 		return (ft_ptrfree(split), 1);
	// else if (!ft_strncmp("sp", split[0], ft_strlen(split[0])))
	// 	if (parse_sp())
	// 		return (ft_ptrfree(split), 1);
	// else if (!ft_strncmp("pl", split[0], ft_strlen(split[0])))
	// 	if (parse_pl())
	// 		return (ft_ptrfree(split), 1);
	// else if (!ft_strncmp("cy", split[0], ft_strlen(split[0])))
	// 	if (parse_cy())
	// 		return (ft_ptrfree(split), 1);
	ft_ptrfree(split);
	return (0);
}

// Main Parser Function
int	parser(char *filename, t_object *objects)
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
		parse_line(line, objects);
		line = get_next_line(fd);
	}
	return (0);
}
