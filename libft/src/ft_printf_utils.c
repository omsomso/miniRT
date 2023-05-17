/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 10:58:51 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/02 02:42:06 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_uns_fd(unsigned int n, int fd)
{
	if (n >= 0 && n < 10)
		ft_putchar_fd(n + '0', fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_uns_fd(n *(-1), fd);
	}
	else
	{
		ft_putnbr_uns_fd(n / 10, fd);
		ft_putnbr_uns_fd(n % 10, fd);
	}
}

int	ft_nblen(long nb)
{
	int	len;

	len = 1;
	if (nb < 0)
		len++;
	while (nb / 10 != 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

int	ft_puthex(unsigned long nb, unsigned long nbcpy, char *hex)
{
	int	count;

	count = 1;
	if (nb == 0 && nbcpy == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	if (nb == 0)
		return (0);
	count += ft_puthex(nb / 16, nbcpy, hex);
	write(1, &hex[nb % 16], 1);
	return (count);
}

int	ft_putaddr(void *what)
{
	unsigned long	hey;
	int				h;

	h = 2;
	hey = (unsigned long)what;
	ft_putstr_fd("0x", 1);
	h += ft_puthex(hey, hey, "0123456789abcdef");
	return (h);
}
