/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_strings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:23:06 by armarake          #+#    #+#             */
/*   Updated: 2025/06/19 11:36:43 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void	free_result(char ***array)
{
	int	i;

	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free((*array));
}

static char	*create_string(t_ht_item *item, int mode)
{
	int		len;
	char	*str;

	if (!item->print && mode)
		return (ft_strdup(item->key));
	len = safe_strlen(item->key) + safe_strlen(item->value) + 1;
	if (mode)
		len += 2;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_memmove(str, item->key, safe_strlen(item->key));
	ft_memmove(str + safe_strlen(item->key), "=", 1);
	if (mode)
	{
		ft_memmove(str + safe_strlen(item->key) + 1, "\"", 1);
		ft_memmove(str + safe_strlen(item->key) + 2, item->value,
			safe_strlen(item->value));
		ft_memmove(str + safe_strlen(item->key) + 2 + safe_strlen(item->value),
			"\"", 1);
	}
	else
		ft_memmove(str + safe_strlen(item->key) + 1, item->value,
			safe_strlen(item->value));
	return (str[len] = '\0', str);
}

static int	count_length(t_hash_table *ht)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < ht->size)
	{
		if (ht->items[i] != NULL && ht->items[i] != ht->deleted
			&& ht->items[i]->print)
			len++;
		i++;
	}
	return (len);
}

char	**ht_to_strings(t_hash_table *ht, int mode)
{
	int		i;
	int		j;
	int		len;
	char	**result;

	len = count_length(ht);
	result = malloc(sizeof(char *) * (len + 1));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < ht->size)
	{
		if (ht->items[i] != NULL && ht->items[i] != ht->deleted)
		{
			if (!ht->items[i]->print && !mode)
				continue ;
			result[j] = create_string(ht->items[i], mode);
			if (!result[j])
				return (free_result(&result), NULL);
			j++;
		}
	}
	result[len] = NULL;
	return (result);
}
