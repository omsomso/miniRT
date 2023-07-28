/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:02:44 by fcullen           #+#    #+#             */
/*   Updated: 2023/07/20 22:34:19 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

float	ft_atof(const char *s)
{
	float	res;
	float	sign;
	float	decimal;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	decimal = 0.1;
	while (s[i] && ft_isspace(s[i]) == 1)
		i++;
	if (s[i] == '+' && ft_isdigit(s[i + 1]) == 0)
		return (0);
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] && ft_isdigit(s[i]))
	{
		res = res * 10 + (s[i] - '0');
		i++;
	}
	if (s[i] == '.')  // handle fractional part
	{
		i++;
		while (s[i] && ft_isdigit(s[i]) == 1)
		{
			res += (s[i] - '0') * decimal;
			decimal *= 0.1;
			i++;
		}
	}
	return (res * sign);
}
