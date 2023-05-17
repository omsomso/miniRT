/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25                               #+#    #+#             */
/*   Updated: 2023/03/02                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	llen;

	i = 0;
	llen = ft_strlen(little);
	if (!*little)
		return ((char *) big);
	if (len == 0)
		return (NULL);
	if (len < llen)
		return (NULL);
	len -= llen;
	while (big[i] != '\0' && i <= len)
	{
		if (ft_strncmp(little, &big[i], llen) == 0)
			return ((char *) &big[i]);
		i++;
	}
	return (NULL);
}
