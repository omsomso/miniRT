/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25                               #+#    #+#             */
/*   Updated: 2023/03/02                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	size_t		slen;
	char		*dup;

	slen = ft_strlen(s);
	dup = malloc(sizeof(char) * slen + 1);
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s, slen + 1);
	return (dup);
}
