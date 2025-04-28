/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:45:33 by nasargsy          #+#    #+#             */
/*   Updated: 2025/03/11 14:10:29 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char *)s;
	if (!p)
		return (NULL);
	while (*p && *p != (char)c)
		p++;
	if (*p == (char)c)
		return (p);
	return (NULL);
}
