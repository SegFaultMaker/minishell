/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_strings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:23:06 by armarake          #+#    #+#             */
/*   Updated: 2025/05/03 23:18:15 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envoirment.h"

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

static char	*create_string(t_ht_item *item)
{
	int		len;
	char	*str;

	len = ft_strlen(item->key) + ft_strlen(item->value) + 1;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_memmove(str, item->key, ft_strlen(item->key));
	ft_memmove(str + ft_strlen(item->key), "=", 1);
	ft_memmove(str + ft_strlen(item->key) + 1, item->value,
		ft_strlen(item->value));
	str[len] = '\0';
	return (str);
}

char	**ht_to_strings(t_hash_table *ht)
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
			result[j] = create_string(ht->items[i]);
			if (!result[j])
				return (free_result(result), NULL);
			j++;
		}
		i++;
	}
	result[ht->count] = NULL;
	return (result);
}
