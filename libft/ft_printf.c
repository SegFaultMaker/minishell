/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:34:15 by nasargsy          #+#    #+#             */
/*   Updated: 2025/03/19 14:46:02 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_specs(char c, va_list args)
{
	int	n;

	n = 0;
	if (c == 'c')
		n += ft_putchar(va_arg(args, int));
	else if (c == 's')
		n += ft_putstr(va_arg(args, char *));
	else if (c == 'p')
	{
		n += ft_putstr("0x");
		n += ft_putnbr_hex(va_arg(args, unsigned long), 'X');
	}
	else if (c == 'd' || c == 'i')
		n += ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		n += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		n += ft_putnbr_hex(va_arg(args, unsigned long), c);
	else if (c == '%')
		n += ft_putchar('%');
	return (n);
}

int	ft_printf(const char *str, ...)
{
	int		lenght;
	va_list	args;

	lenght = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			lenght += ft_specs(*str, args);
		}
		else
			lenght += ft_putchar(*str);
		str++;
	}
	va_end(args);
	return (lenght);
}
