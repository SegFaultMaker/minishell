/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:33:28 by nasargsy          #+#    #+#             */
/*   Updated: 2025/01/25 13:07:32 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*p1;
	char	*p2;
	size_t	i;

	p1 = (char *)s1;
	p2 = (char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && p1[i] == p2[i])
		i++;
	return ((unsigned char)p1[i] - (unsigned char)p2[i]);
}
