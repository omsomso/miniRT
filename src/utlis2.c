/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:22:30 by fcullen           #+#    #+#             */
/*   Updated: 2023/09/26 16:25:11 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

float	process_decimal(const char *s, int i)
{
	float	decimal;
	float	res;

	decimal = 0.1;
	res = 0;
	i++;
	while (s[i] && ft_isdigit(s[i]))
	{
		res += (s[i] - '0') * decimal;
		decimal *= 0.1;
		i++;
	}
	return (res);
}

float	ft_atof(const char *s)
{
	float	res;
	float	sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] && ft_isdigit(s[i]))
		res = res * 10 + (s[i++] - '0');
	if (s[i] == '.')
		res += process_decimal(s, i);
	return (res * sign);
}
