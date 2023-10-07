/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:17:28 by kpawlows          #+#    #+#             */
/*   Updated: 2023/10/07 20:23:02 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// frees a string array
void	ft_ptrfree(char **s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return ;
	while (s[i])
	{
		free(s[i]);
		s[i++] = NULL;
	}
	free(s);
}

// duplicates a string array
char	**ft_ptrdup(char **s, int n)
{
	int		i;
	char	**out;

	i = -1;
	out = malloc(sizeof(char *) * (n + 1));
	if (!out)
		return (NULL);
	while (++i < n)
		out[i] = ft_strdup(s[i]);
	out[i] = NULL;
	return (out);
}

// duplicates a string array, frees the original
char	**ft_ptrdup_f(char **s, int n)
{
	int		i;
	char	**out;

	i = -1;
	out = malloc(sizeof(char *) * (n + 1));
	if (!out)
		return (NULL);
	while (++i < n)
		out[i] = ft_strdup(s[i]);
	out[i] = NULL;
	ft_ptrfree(s);
	return (out);
}

// coutns the number of strings in a null terminated string array
int	ft_ptrcount(char **s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != NULL)
		i++;
	return (i);
}
