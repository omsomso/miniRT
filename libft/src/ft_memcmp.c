/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24                               #+#    #+#             */
/*   Updated: 2023/03/02                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*s1tmp;
	const char	*s2tmp;

	i = 0;
	s1tmp = s1;
	s2tmp = s2;
	if (n == 0)
		return (0);
	while (i < (n - 1) && s1tmp[i] == s2tmp[i])
		i++;
	if (s1tmp[i] != s2tmp[i])
		return ((unsigned char)s1tmp[i] - (unsigned char)s2tmp[i]);
	return (0);
}
