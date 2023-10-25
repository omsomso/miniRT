/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaphod <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:22:30 by zaphod           #+#    #+#             */
/*   Updated: 2023/10/13 16:51:46 by zaphod          ###   ########.fr       */
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
