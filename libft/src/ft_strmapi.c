/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 00:09:50 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/02 02:41:31 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int			i;
	int			slen;
	char		*s2;

	i = 0;
	slen = ft_strlen(s);
	s2 = malloc(sizeof(char) * slen + 1);
	if (s2 == NULL)
		return (NULL);
	while (i < slen)
	{
		s2[i] = f(i, s[i]);
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
