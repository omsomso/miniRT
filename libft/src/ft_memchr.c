/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:24:14 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/02 02:40:16 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*s2;
	char		tmp;

	i = 0;
	tmp = (char) c;
	if (!s)
		return (NULL);
	s2 = s;
	while (i < n)
	{
		if (s2[i] == tmp)
			return ((void *) &s2[i]);
		i++;
	}
	return (NULL);
}
