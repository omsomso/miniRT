/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:58:02 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/02 02:40:03 by kpawlows         ###   ########.fr       */
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
