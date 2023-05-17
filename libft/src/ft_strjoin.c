/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:25:49 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/02 02:41:17 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	s1len;
	size_t	s2len;
	char	*join;

	i = -1;
	j = 0;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	join = malloc(sizeof(char) * (s1len + s2len) + 1);
	if (join == NULL)
		return (NULL);
	while (++i < s1len)
		join[i] = s1[i];
	while (j < s2len)
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	return (join);
}

char	*ft_strjoin_ff(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	s1len;
	size_t	s2len;
	char	*join;

	i = -1;
	j = -1;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	join = malloc(sizeof(char) * (s1len + s2len) + 1);
	if (join == NULL)
		return (NULL);
	while (++i < s1len)
		join[i] = s1[i];
	while (++j < s2len)
		join[i++] = s2[j];
	join[i] = '\0';
	free(s1);
	return (join);
}

char	*ft_strjoin_fs(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	s1len;
	size_t	s2len;
	char	*join;

	i = -1;
	j = -1;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	join = malloc(sizeof(char) * (s1len + s2len) + 1);
	if (join == NULL)
		return (NULL);
	while (++i < s1len)
		join[i] = s1[i];
	while (++j < s2len)
		join[i++] = s2[j];
	join[i] = '\0';
	free(s2);
	return (join);
}

char	*ft_strjoin_fb(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	s1len;
	size_t	s2len;
	char	*join;

	i = -1;
	j = -1;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	join = malloc(sizeof(char) * (s1len + s2len) + 1);
	if (join == NULL)
		return (NULL);
	while (++i < s1len)
		join[i] = s1[i];
	while (++j < s2len)
		join[i++] = s2[j];
	join[i] = '\0';
	free(s1);
	free(s2);
	return (join);
}
