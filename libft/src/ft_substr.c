/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:25:49 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/02 02:41:49 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start + len > slen)
		len = slen;
	sub = malloc(sizeof(char) * len + 1);
	if (!sub)
		return (NULL);
	while (start < slen && i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
