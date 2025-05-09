/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_strings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:23:06 by armarake          #+#    #+#             */
/*   Updated: 2025/05/08 16:11:49 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	free_result(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	*create_string(t_ht_item *item, int mode)
{
	int		len;
	char	*str;

	len = ft_strlen(item->key) + ft_strlen(item->value) + 1;
	if (mode)
		len += 2;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_memmove(str, item->key, ft_strlen(item->key));
	ft_memmove(str + ft_strlen(item->key), "=", 1);
	if (mode)
	{
		ft_memmove(str + ft_strlen(item->key) + 1, "\"", 1);
		ft_memmove(str + ft_strlen(item->key) + 2, item->value,
			ft_strlen(item->value));
		ft_memmove(str + ft_strlen(item->key) + 2 + ft_strlen(item->value),
			"\"", 1);
	}
	else
		ft_memmove(str + ft_strlen(item->key) + 1, item->value,
			ft_strlen(item->value));
	str[len] = '\0';
	return (str);
}

char	**ht_to_strings(t_hash_table *ht, int mode)
{
	int		i;
	int		j;
	char	**result;

	result = malloc(sizeof(char *) * (ht->count + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ht->size)
	{
		if (ht->items[i] != NULL && ht->items[i] != ht->deleted)
		{
			result[j] = create_string(ht->items[i], mode);
			if (!result[j])
				return (free_result(result), NULL);
			j++;
		}
		i++;
	}
	result[ht->count] = NULL;
	return (result);
}
