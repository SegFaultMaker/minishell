/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:33:39 by nasargsy          #+#    #+#             */
/*   Updated: 2025/01/10 13:59:59 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*ptr;
	int		i;

	ptr = malloc(ft_strlen(src) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (*src)
	{
		ptr[i] = *src++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
