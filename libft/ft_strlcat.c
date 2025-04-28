/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:33:08 by nasargsy          #+#    #+#             */
/*   Updated: 2025/01/26 13:14:18 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t nb)
{
	size_t	dstsize;
	size_t	srcsize;
	size_t	i;

	dstsize = 0;
	srcsize = ft_strlen(src);
	i = 0;
	while (dstsize < nb && dest[dstsize] != '\0')
		dstsize++;
	if (nb <= dstsize)
		return (nb + srcsize);
	while (src[i] != '\0' && dstsize + i < nb - 1)
	{
		dest[dstsize + i] = src[i];
		i++;
	}
	dest[dstsize + i] = '\0';
	return (dstsize + srcsize);
}
