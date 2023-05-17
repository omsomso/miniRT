/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:15:32 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/02 02:42:01 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*gnl_get_line(char **rest)
{
	int		len;
	char	*out;
	char	*tmp;

	len = ft_strlen(*rest);
	out = NULL;
	if (gnl_find_char(*rest, '\n', len) == 0 && rest[0][0] != '\n')
	{
		if (*rest[0] != '\0')
			out = ft_substr(*rest, 0, gnl_find_char(*rest, '\0', len));
		free(*rest);
		*rest = NULL;
		return (out);
	}
	out = ft_substr(*rest, 0, gnl_find_char(*rest, '\n', len) + 1);
	tmp = ft_substr(*rest, gnl_find_char(*rest, '\n', len) + 1, len);
	free(*rest);
	*rest = ft_substr(tmp, 0, ft_strlen(tmp));
	free(tmp);
	return (out);
}

void	gnl_read_buffer(char **rest, int fd)
{
	char	*buf;
	char	*tmp;
	int		pos;

	pos = 1;
	while (pos > 0)
	{
		buf = malloc((GNL_BUFFER_SIZE + 1) * sizeof(char));
		pos = read(fd, buf, GNL_BUFFER_SIZE);
		if (pos == -1)
			buf[0] = '\0';
		else
			buf[pos] = '\0';
		tmp = ft_strjoin(rest[0], buf);
		free(buf);
		free(rest[0]);
		rest[0] = ft_substr(tmp, 0, ft_strlen(tmp));
		free(tmp);
		if (gnl_find_char(rest[0], '\n', ft_strlen(rest[0])))
			break ;
	}
}

char	*get_next_line(int fd)
{
	static char		*rest;
	char			*out;

	out = NULL;
	if (fd < 0 || GNL_BUFFER_SIZE <= 0)
		return (NULL);
	if (!rest)
	{
		rest = malloc(1);
		rest[0] = '\0';
	}
	gnl_read_buffer(&rest, fd);
	out = gnl_get_line(&rest);
	if (out == NULL)
		return (NULL);
	return (out);
}
