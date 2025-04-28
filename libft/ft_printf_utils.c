/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:50:19 by nasargsy          #+#    #+#             */
/*   Updated: 2025/03/19 16:44:49 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	return (write(1, str, ft_strlen(str)));
}

int	ft_putnbr(int nb)
{
	int	size;

	size = 0;
	if (nb == -2147483648)
		return (write(1, "-2147483648", 11));
	if (nb < 0)
	{
		size += ft_putchar('-');
		nb *= -1;
	}
	if (nb > 9)
	{
		size += ft_putnbr(nb / 10);
		nb %= 10;
	}
	size += ft_putchar(nb + 48);
	return (size);
}

int	ft_putnbr_unsigned(unsigned int nb)
{
	int	size;

	size = 0;
	if (nb > 9)
	{
		size += ft_putnbr_unsigned(nb / 10);
		nb %= 10;
	}
	size += ft_putchar(nb + 48);
	return (size);
}

int	ft_putnbr_hex(unsigned int nb, char format)
{
	int	size;

	size = 0;
	if (nb > 15)
	{
		size += ft_putnbr_unsigned(nb / 16);
		nb %= 16;
	}
	if (nb > 9)
	{
		if (format == 'X')
			size += ft_putchar((nb - 10) + 'A');
		else if (format == 'x')
			size += ft_putchar((nb - 10) + 'a');
	}	
	else
		size += ft_putchar(nb + 48);
	return (size);
}
