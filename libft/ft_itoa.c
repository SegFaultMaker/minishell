/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:59:50 by nasargsy          #+#    #+#             */
/*   Updated: 2025/01/10 17:37:54 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(int num)
{
	int	count;

	count = 0;
	if (num < 0)
		count++;
	while (num)
	{
		num /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int num)
{
	int		len;
	int		i;
	char	*res;

	if (!num)
		return (ft_strdup("0"));
	if (num == -2147483648)
		return (ft_strdup("-2147483648"));
	len = length(num);
	res = (char *)malloc(len + 1);
	if (!res)
		return (NULL);
	if (num < 0)
	{
		res[0] = '-';
		num *= -1;
	}
	i = len - 1;
	res[len] = '\0';
	while (num)
	{
		res[i--] = (num % 10) + '0';
		num /= 10;
	}
	return (res);
}
