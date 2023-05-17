/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 15:08:56 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/02 02:39:20 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	dst_len;
	unsigned int	src_len;

	i = 0;
	j = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = dst_len;
	if (n == 0)
		return (src_len);
	if (n < dst_len)
		return (n + src_len);
	while (i < (n - 1) && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (src_len + dst_len);
}
