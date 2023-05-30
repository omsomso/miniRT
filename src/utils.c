/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:02:44 by fcullen           #+#    #+#             */
/*   Updated: 2023/05/30 13:14:12 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

float	ft_atof(const char *s)
{
	float	res;
	float	sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while (s[i] && ft_isspace(s[i]) == 1)
		i++;
	if (s[i] == '+' && ft_isdigit(s[i + 1]) == 0)
		return (0);
	if (s[i] == '+')
		i++;
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (s[i] && ft_isdigit(s[i]) == 1)
	{
		res *= 10;
		res += (s[i] - '0');
		i++;
	}
	return (res * sign);
}
