/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/22 22:58:11 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Returns 1 if line is only spaces, tabs etc
int	line_isspace(char *line)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			space++;
		i++;
	}
	if (space == i)
		return (1);
	return (0);
}

// Replaces all tabs, multiple spaces etc with spaces for split
char	*line_fixspace(char *line)
{
	int		i;
	char	*newline;

	i = 0;
	newline = malloc(sizeof(char) * ft_strlen(line) + 1);
	if (!newline)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\n')
			newline[i] = '\n';
		else if (ft_isspace(line[i]))
			newline[i] = ' ';
		else
			newline[i] = line[i];
		i++;
	}
	newline[i] = '\0';
	free(line);
	return (newline);
}

// Returns 1 if scene lack a required element (A, C, L)
int	check_scene(t_data *data)
{
	if (!data->ambient_light)
	{
		write(2, "Error: No ambient light\n", 25);
		return (1);
	}
	if (!data->camera)
	{
		write(2, "Error: No camera\n", 17);
		return (1);
	}
	if (!data->light)
	{
		write(2, "Error: No light\n", 16);
		return (1);
	}
	return (0);
}

// Inits scene info in data struct
int	init_scene(t_data *data)
{
	data->ambient_light = NULL;
	data->camera = NULL;
	data->light = NULL;
	return (0);
}

// Returns 1 if string has invalid number characters (for color & pos)
int	ch_nb(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && !ft_isspace(s[i]))
		{
			if (!(s[i] == '.' || s[i] == '-' || s[i] == '+'))
				return (1);
		}
		i++;
	}
	return (0);
}
