/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/10/25 19:11:13 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Returns 1 if line consists only of whitespaces
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

// Replaces all whitespaces except \n with spaces for split
char	*line_fixspace(char *line)
{
	int		i;
	char	*newline;

	i = 0;
	newline = malloc(sizeof(char) * ft_strlen(line) + 1);
	if (!newline)
		exit(1);
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

// Returns 1 if the scene lacks a required element (A, C, L)
int	check_scene(t_data *data)
{
	if (!data->ambient_light)
	{
		write(2, "Error\nNo ambient light\n", 25);
		exit(1);
	}
	if (!data->camera)
	{
		write(2, "Error\nNo camera\n", 17);
		exit(1);
	}
	if (!data->light)
	{
		write(2, "Error\nNo light\n", 16);
		exit(1);
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
		// if (ft_isspace(s[i]))
		// {
		// 	printf("ohnannna un espaaaceee\n");
		// 	return (0);
		// }
	}
	return (0);
}

char	*line_rm_isspace(char *s)
{
	int		i;
	int		j;
	char	*out;

	out = malloc(sizeof(char) * ft_strlen(s));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
		{
			out[j] = s[i];
			j++;
			i++;
		}
		else
			i++;
	}
	out[j] = 0x00;
	free(s);
	return (out);
}