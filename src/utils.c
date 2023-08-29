/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:02:44 by fcullen           #+#    #+#             */
/*   Updated: 2023/08/29 17:52:02 by kpawlows         ###   ########.fr       */
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

char	*ft_ftoa(float f)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*out;

	tmp1 = ft_itoa((int)f);
	tmp2 = ft_strjoin_ff(tmp1, ".");
	tmp3 = ft_itoa((int)((f - (int)f) * 100));
	out = ft_strjoin_fb(tmp2, tmp3);
	return (out);
}
