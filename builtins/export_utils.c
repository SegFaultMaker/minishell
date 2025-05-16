/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:49:08 by armarake          #+#    #+#             */
/*   Updated: 2025/05/16 22:12:18 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
