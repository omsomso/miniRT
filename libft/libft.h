/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 02:13:23 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/02 02:42:15 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# define GNL_BUFFER_SIZE 64

int		ft_atoi(const char *s);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);

char	*ft_itoa(int n);
char	**ft_split(char const *s, char const c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_ff(char *s1, char *s2);
char	*ft_strjoin_fs(char *s1, char *s2);
char	*ft_strjoin_fb(char *s1, char *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);

size_t	ft_strlcat(char *dst, const char *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlen(const char *s);

char	*get_next_line(int fd);
void	gnl_read_buffer(char **rest, int fd);
char	*gnl_get_line(char **rest);
int		gnl_strlen(const char *s);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_strjoin(char const *s1, char const *s2);
int		gnl_find_char(const char *s, int c, int n);

void	ft_putnbr_uns_fd(unsigned int n, int fd);
int		ft_nblen(long nb);
int		ft_puthex(unsigned long nb, unsigned long nbcpy, char *hex);
int		ft_putaddr(void *what);
int		ft_add_chars(char c, long arg);
int		ft_put_value(char c, long arg);
int		ft_printf(const char *argv, ...);

#endif