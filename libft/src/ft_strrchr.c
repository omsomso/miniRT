/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24                               #+#    #+#             */
/*   Updated: 2023/03/02                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				slen;
	unsigned char	tmp;

	slen = ft_strlen(s);
	tmp = (unsigned char) c;
	while (slen >= 0)
	{
		if (s[slen] == tmp)
			return ((char *) &s[slen]);
		slen--;
	}
	return (NULL);
}
