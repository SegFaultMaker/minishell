/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:08:27 by nasargsy          #+#    #+#             */
/*   Updated: 2025/01/09 19:26:56 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	keylen;

	if (!(*needle) || !needle)
		return ((char *)haystack);
	keylen = ft_strlen(needle);
	while (*haystack && n >= keylen)
	{
		if (*haystack == *needle && !(ft_strncmp(haystack, needle, keylen)))
			return ((char *)haystack);
		++haystack;
		--n;
	}
	return (NULL);
}
