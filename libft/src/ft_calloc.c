/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25                               #+#    #+#             */
/*   Updated: 2023/03/02                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*coc;

	i = 0;
	coc = malloc(nmemb * size);
	if (coc == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		coc[i] = '\0';
		i++;
	}
	return ((void *) coc);
}
