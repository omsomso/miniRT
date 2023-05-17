/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:24:14 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/02 02:41:41 by kpawlows         ###   ########.fr       */
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
