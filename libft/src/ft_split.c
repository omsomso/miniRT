/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:15:36 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/02 02:40:55 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_issep(char const *s, char c, int i)
{
	while (s[i] == c && s[i] != '\0')
		i++;
	return (i);
}

int	ft_isword(char const *s, char c, int i)
{
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		i = ft_issep(s, c, i);
		if (s[i] != c && s[i] != '\0')
			count++;
		i = ft_isword(s, c, i);
	}
	return (count);
}

char	**ft_split(char const *s, char const c)
{
	int		i;
	int		j;
	int		wc;
	char	**split;

	i = 0;
	j = 0;
	wc = ft_wordcount(s, c);
	split = malloc(sizeof(char *) * wc + sizeof(char *));
	if (split == NULL)
		return (NULL);
	while (i < wc)
	{
		j = ft_issep(s, c, j);
		split[i] = malloc(sizeof(char) * ft_isword(s, c, j) - j + 1);
		ft_strlcpy(split[i], &s[j], ft_isword(s, c, j) - j + 1);
		j = ft_isword(s, c, j);
		i++;
	}
	split[i] = NULL;
	return (split);
}
