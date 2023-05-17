/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:25:49 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/02 02:41:46 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isset(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	s1len;

	i = 0;
	s1len = ft_strlen(s1);
	while (ft_isset(set, s1[i]) == 1)
		i++;
	if (i == s1len)
		return (ft_substr(s1, 0, 0));
	while (s1len != 0 && ft_isset(set, s1[s1len - 1]) == 1)
		s1len--;
	return (ft_substr(s1, i, s1len - i));
}
