/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:49:08 by armarake          #+#    #+#             */
/*   Updated: 2025/05/10 16:04:53 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*no_free_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*get_key_end(char *arg, int mode)
{
	char	*key_end;

	if (mode == JOIN_MODE)
		key_end = ft_strchr(arg, '+');
	else
		key_end = ft_strchr(arg, '=');
	return (key_end);
}

char	*get_key(char *arg, char *key_end)
{
	int		i;
	int		len;
	char	*key;

	len = key_end - arg;
	if (len == 0)
		return (NULL);
	i = -1;
	while (i++ < len)
		if (arg[i] == ' ')
			return (NULL);
	key = malloc(len + 1);
	ft_memmove(key, arg, len);
	key[len] = '\0';
	return (key);
}

void	free_key_value(char *key, char *value, char *existing, int mode)
{
	if (mode == JOIN_MODE && existing)
	{
		free(value);
		value = NULL;
	}
	free(key);
	key = NULL;
}
