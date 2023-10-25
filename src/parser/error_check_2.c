/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/10/25 20:08:21 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Returns 1 if cy data is missing or invalid
int	check_cy(char **s)
{
	if (ft_ptrcount(s) != 6)
	{
		write(2, "Error\nCylinder parameters invalid\n", 35);
		exit(1);
	}
	if (ch_nb(s[3]) || ft_atof(s[3]) <= 0)
	{
		write(2, "Error\nCylinder diameter must be a positive number\n", 51);
		exit(1);
	}
	if (ch_nb(s[4]) || ft_atof(s[4]) <= 0)
	{
		write(2, "Error\nCylinder height must be a positive number\n", 49);
		exit(1);
	}
	if (check_pos(s[1]))
		exit(1);
	if (check_normal(s[2]))
		exit(1);
	if (check_color(s[5]))
		exit(1);
	return (0);
}

// Returns 1 if position is missing or invalid
int	check_pos(char *position)
{
	char	**pos;

	pos = ft_split(position, ',');
	if (!pos || !pos[0] || !pos[1] || !pos[2] || ft_ptrcount(pos) != 3)
	{
		write(2, "Error\nObject position coordinates invalid\n", 43);
		ft_ptrfree(pos);
		exit(1);
	}
	else if (ch_nb(pos[0]) || ch_nb(pos[1]) || ch_nb(pos[2]))
	{
		write(2, "Error\nObject position coordinates must be numbers\n", 51);
		ft_ptrfree(pos);
		exit(1);
	}
	ft_ptrfree(pos);
	return (0);
}

// Returns 1 and writes error if color is invalid
int	check_color(char *color)
{
	int		err;
	char	**col;

	// printf("color = %s\n", color);
	// color = line_rm_isspace(color);
	// printf("color rms = %s\n", color);
	col = ft_split(color, ',');
	printf("%s,%s,%s.\n", col[0], col[1], col[2]);
	err = 0;
	if (!col || !col[0] || !col[1] || !col[2] || ft_ptrcount(col) != 3)
	{
		write(2, "Error\nColor parameters invalid\n", 32);
		exit(1);
	}
	else if (ch_nb(col[0]) || ft_atoi(col[0]) < 0 || ft_atoi(col[0]) > 255)
		err = 1;
	else if (ch_nb(col[1]) || ft_atoi(col[1]) < 0 || ft_atoi(col[1]) > 255)
		err = 1;
	else if (ch_nb(col[2]) || ft_atoi(col[2]) < 0 || ft_atoi(col[2]) > 255)
		err = 1;
	if (err == 1)
	{
		write(2, "Error\nColor parameters must be nbs between 0 & 255\n", 52);
		ft_ptrfree(col);
		exit(1);
	}
	// printf("col[2] = %s\n", col[2]);
	// printf("ch_nb col[2] = %d\n", ch_nb(col[2]));
	// printf("col[2] = %d\n", ft_atoi(col[2]));
	ft_ptrfree(col);
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
		write(2, "Error\nNormal vectors must be between -1 & 1\n", 45);
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
	exit(1);
}
