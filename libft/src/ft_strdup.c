/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:29:19 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/02 02:41:07 by kpawlows         ###   ########.fr       */
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
