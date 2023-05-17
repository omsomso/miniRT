/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 23:21:30 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/02 02:40:38 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_add_chars(char c, long arg)
{
	int	charcount;

	charcount = 0;
	if (c == 'c' || c == '%' || c == 'k')
		charcount = 1;
	if (c == 'd' || c == 'i')
		charcount = ft_nblen((int) arg);
	if (c == 'u')
		charcount = ft_nblen((unsigned int) arg);
	if (c == 's' && (char *)arg != NULL)
		charcount = ft_strlen((char *)arg);
	if (c == 's' && (char *)arg == NULL)
	{
		charcount = 6;
		ft_putstr_fd("(null)", 1);
	}
	return (charcount);
}

int	ft_put_value(char c, long arg)
{
	int	h;

	h = 0;
	if (c == 'c' || c == '%' || c == 'k')
		ft_putchar_fd(arg, 1);
	if (c == 'd' || c == 'i')
		ft_putnbr_fd(arg, 1);
	if (c == 'u')
		ft_putnbr_uns_fd((unsigned int)arg, 1);
	if (c == 's' && (char *)arg != NULL)
		ft_putstr_fd((char *)arg, 1);
	if (c == 'x')
		h = ft_puthex((unsigned int)arg, (unsigned int)arg, "0123456789abcdef");
	if (c == 'X')
		h = ft_puthex((unsigned int)arg, (unsigned int)arg, "0123456789ABCDEF");
	if (c == 'p')
		h = ft_putaddr((void *)arg);
	return (ft_add_chars(c, arg) + h);
}

int	ft_printf(const char *argv, ...)
{
	int		i;
	int		charcount;
	va_list	args;

	va_start(args, argv);
	i = -1;
	charcount = 0;
	while (argv[++i] != '\0')
	{
		if (argv[i] == '%')
		{
			if (argv[++i] == '%')
				charcount += ft_put_value('k', argv[i]);
			else
				charcount += ft_put_value(argv[i], va_arg(args, long));
		}
		else
			charcount += ft_put_value('k', argv[i]);
	}
	va_end(args);
	return (charcount);
}
