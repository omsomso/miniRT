/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 05:18:18 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/02 02:39:58 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v')
		return (1);
	return (0);
}

int	ft_atoi(const char *s)
{
	int	res;
	int	sign;
	int	i;

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
