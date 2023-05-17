/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 07:23:27 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/02 02:39:33 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_intcharnb(int n)
{
	int	size;

	size = 0;
	if (n < 0)
		size++;
	while (n / 10 != 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

void	ft_sign(char *s, int *sign, int *n)
{
		s[0] = '-';
		*n *= -1;
		*sign = 1;
}

char	*ft_min(char *s)
{
	ft_strlcpy(s, "-2147483648", 12);
	return (s);
}

char	*ft_itoa(int n)
{
	int		i;
	int		size;
	int		sign;
	char	*s;

	size = ft_intcharnb(n);
	sign = 0;
	s = malloc(sizeof(char) * size + 2);
	if (s == NULL)
		return (NULL);
	if (n == -2147483648)
		return (ft_min(s));
	if (n < 0)
		ft_sign(s, &sign, &n);
	i = size;
	while (i >= sign)
	{
		s[i] = (n % 10 + '0');
		n /= 10;
		i--;
	}
	s[size + 1] = '\0';
	return (s);
}
