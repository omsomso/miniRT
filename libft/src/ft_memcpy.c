/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24                               #+#    #+#             */
/*   Updated: 2023/03/02                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dst2;
	const char	*src2;

	i = 0;
	dst2 = dst;
	src2 = src;
	if (!dst2 && !src2)
		return (NULL);
	while (i < n)
	{
		dst2[i] = src2[i];
		i++;
	}
	dst = dst2;
	return (dst);
}
