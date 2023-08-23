/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:44:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/23 02:32:39 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Returns 1 if ambient light data is missing or invalid
int	check_a(char **s)
{
	float		ratio;
	static int	count = 0;

	count++;
	if (ft_ptrcount(s) != 3)
	{
		write(2, "Error: Ambient light parameters invalid\n", 40);
		return (1);
	}
	if (count > 1)
	{
		write(2, "Error: There can only be 1 Ambient light\n", 41);
		return (1);
	}
	ratio = ft_atof(s[1]);
	if (ratio < 0 || ratio > 1)
	{
		write(2, "Error: Ambient light ratio must be between 0 and 1\n", 51);
		return (1);
	}
	if (check_color(s[2]))
		return (1);
	return (0);
}

// Returns 1 if light data is missing or invalid
int	check_l(char **s)
{
	static int	count = 0;

	count++;
	if (!s[1] || !s[2] || ft_ptrcount(s) > 4)
	{
		write(2, "Error: Light parameters invalid\n", 33);
		return (1);
	}
	if (count > 1)
	{
		write(2, "Error: There can only be 1 Light\n", 33);
		return (1);
	}
	if (check_l_brightness(ft_atof(s[2])))
		return (1);
	if (check_pos(s[1]))
		return (1);
	if (s[3])
	{
		if (check_color(s[3]))
			return (1);
	}
	return (0);
}

// Returns 1 if camera data is missing or invalid
int	check_c(char **s)
{
	int			fov;
	static int	count = 0;

	count++;
	if ((ft_ptrcount(s) != 4) || (s[1] && check_pos(s[1])))
	{
		write(2, "Error: Camera parameters invalid\n", 33);
		return (1);
	}
	if (count > 1)
	{
		write(2, "Error: There can only be 1 Camera\n", 34);
		return (1);
	}
	fov = ft_atoi(s[3]);
	if (fov < 0 || fov > 180)
	{
		write(2, "Error: Camera FOV must be between 0 and 180\n", 44);
		return (1);
	}
	if (check_normal(s[2]))
		return (1);
	return (0);
}

// Returns 1 if plane data is missing or invalid
int	check_pl(char **s)
{
	if (!s[1] || !s[2] || !s[3])
	{
		write(2, "Error: Plane parameters missing\n", 33);
		return (1);
	}
	if (ft_ptrcount(s) != 4 || check_pos(s[1]))
	{
		write(2, "Error: Plane parameters invalid\n", 33);
		return (1);
	}
	if (check_color(s[3]))
		return (1);
	if (check_normal(s[2]))
		return (1);
	return (0);
}

// Returns 1 if sphere data is missing or invalid
int	check_sp(char **s)
{
	if (!s[1] || !s[2] || !s[3] || ft_ptrcount(s) != 4)
	{
		write(2, "Error: Sphere parameters invalid\n", 33);
		return (1);
	}
	if (ch_nb(s[2]) || ft_atof(s[2]) <= 0)
	{
		write(2, "Error: Sphere diameter must be a positive number\n", 49);
		return (1);
	}
	if (check_pos(s[1]))
		return (1);
	if (check_color(s[3]))
		return (1);
	return (0);
}
