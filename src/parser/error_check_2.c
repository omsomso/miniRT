/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/22 22:56:42 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Returns 1 if cy data is missing or invalid
int	check_cy(char **s)
{
	if (!s[1] || !s[2] || !s[3] || s[4] || ft_ptrcount(s) != 5)
	{
		write(2, "Error: Cylinder parameters invalid\n", 35);
		return (1);
	}
	if (ch_nb(s[2]) || ft_atof(s[2]) <= 0)
	{
		write(2, "Error: Cylinder diameter must be a positive number\n", 51);
		return (1);
	}
	if (ch_nb(s[3]) || ft_atof(s[3]) <= 0)
	{
		write(2, "Error: Cylinder height must be a positive number\n", 49);
		return (1);
	}
	if (check_pos(s[1]))
		return (1);
	if (check_color(s[4]))
		return (1);
	return (0);
}

// Returns 1 if position is missing or invalid
int	check_pos(char *position)
{
	char	**pos;

	pos = ft_split(position, ',');
	if (!pos || !pos[0] || !pos[1] || !pos[2] || ft_ptrcount(pos) != 3)
	{
		write(2, "Error: Object position coordinates invalid\n", 43);
		ft_ptrfree(pos);
		return (1);
	}
	else if (ch_nb(pos[0]) || ch_nb(pos[1]) || ch_nb(pos[2]))
	{
		write(2, "Error: Object position coordinates must be numbers\n", 51);
		ft_ptrfree(pos);
		return (1);
	}
	ft_ptrfree(pos);
	return (0);
}

// Returns 1 and writes error if color is invalid
int	check_color(char *color)
{
	int		err;
	char	**col;

	col = ft_split(color, ',');
	err = 0;
	if (!col || !col[0] || !col[1] || !col[2] || ft_ptrcount(col) != 3)
	{
		write(2, "Error: Color parameters invalid\n", 32);
		return (1);
	}
	else if (ch_nb(col[0]) || ft_atoi(col[0]) < 0 || ft_atoi(col[0]) > 255)
		err = 1;
	else if (ch_nb(col[1]) || ft_atoi(col[1]) < 0 || ft_atoi(col[1]) > 255)
		err = 1;
	else if (ch_nb(col[2]) || ft_atoi(col[2]) < 0 || ft_atoi(col[2]) > 255)
		err = 1;
	if (err == 1)
	{
		write(2, "Error: Color parameters must be nbs between 0 & 255\n", 52);
		free(col);
		return (1);
	}
	free(col);
	return (0);
}

// Returns 1 and writes error if normal is invalid
int	check_normal(char *s)
{
	t_v3	*norm;
	int		err;

	err = 0;
	norm = get_vec(ft_split(s, ','));
	if (norm->x < -1 || norm->x > 1)
		err = 1;
	if (norm->y < -1 || norm->y > 1)
		err = 1;
	if (norm->z < -1 || norm->z > 1)
		err = 1;
	free(norm);
	if (err == 1)
	{
		write(2, "Error: Camera normal vector must be between -1 & 1\n", 51);
		return (1);
	}
	return (0);
}

// Returns 1 if finds invalid identifier
int	check_line(char *line, char *name)
{
	if (line_isspace(line))
		return (0);
	if (!ft_strncmp("A", name, ft_strlen(name)))
		return (0);
	else if (!ft_strncmp("C", name, ft_strlen(name)))
		return (0);
	else if (!ft_strncmp("L", name, ft_strlen(name)))
		return (0);
	else if (!ft_strncmp("sp", name, ft_strlen(name)))
		return (0);
	else if (!ft_strncmp("pl", name, ft_strlen(name)))
		return (0);
	else if (!ft_strncmp("cy", name, ft_strlen(name)))
		return (0);
	return (1);
}
