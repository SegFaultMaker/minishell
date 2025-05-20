/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:36:31 by armarake          #+#    #+#             */
/*   Updated: 2025/05/20 15:49:35 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *src)
{
	size_t	i;

	if (!src)
		return (0);
	i = 0;
	while (src[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	len;
	size_t	i;
	size_t	j;

	len = gnl_strlen(s1) + gnl_strlen(s2);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	s1 = NULL;
	return (res);
}

char	*gnl_strchr(const char *str, int c)
{
	unsigned int	i;

	i = 0;
	while (str[i] && str[i] != (char)c)
		i++;
	if (str[i] == (char)c)
		return ((char *)&str[i]);
	else
		return (NULL);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	s_size;
	size_t			i;
	char			*substr;

	if (!s)
		return (NULL);
	s_size = gnl_strlen(s);
	if (start >= s_size)
	{
		substr = (char *)malloc(1);
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	if (len > s_size - start)
		len = s_size - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
