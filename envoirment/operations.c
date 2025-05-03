/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:42:02 by armarake          #+#    #+#             */
/*   Updated: 2025/05/03 23:18:52 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envoirment.h"

static int	update(t_hash_table *ht, t_ht_item *c_item, char *key, char *value)
{
	if ((c_item != NULL && c_item != ht->deleted)
		&& ft_strcmp(c_item->key, key) == 0)
	{
		free(c_item->value);
		c_item->value = ft_strdup(value);
		return (1);
	}
	return (0);
}

int	ht_insert(t_hash_table *ht, char *key, char *value)
{
	int			i;
	int			index;
	t_ht_item	*item;
	t_ht_item	*cur_item;

	if (ht_load(ht) > 70)
		ht_resize_up(ht);
	item = ht_new_item(key, value);
	if (!item)
		return (ht_del_item(item), INSERT_FAILURE);
	index = ht_get_hash(item->key, ht->size, 0);
	cur_item = ht->items[index];
	i = 1;
	while (cur_item != NULL && cur_item != ht->deleted)
	{
		index = ht_get_hash(item->key, ht->size, i++);
		cur_item = ht->items[index];
		if (update(ht, cur_item, key, value))
			return (ht_del_item(item), UPDATE_SUCCESS);
	}
	ht->items[index] = item;
	ht->count++;
	return (INSERT_SUCCESS);
}

char	*ht_search(t_hash_table *ht, char *key)
{
	int			i;
	int			index;
	t_ht_item	*item;

	i = 0;
	while (i < ht->size)
	{
		index = ht_get_hash(key, ht->size, i);
		item = ht->items[index];
		if (item != NULL && item != ht->deleted)
		{
			if (ft_strcmp(item->key, key) == 0)
				return (item->value);
		}
		i++;
	}
	return (NULL);
}

void	ht_delete(t_hash_table *ht, char *key)
{
	int			i;
	int			index;
	t_ht_item	*item;

	if (ht_load(ht) < 10)
		ht_resize_down(ht);
	i = 0;
	while (i < ht->size)
	{
		index = ht_get_hash(key, ht->size, i);
		item = ht->items[index];
		if (item != NULL && item != ht->deleted)
		{
			if (ft_strcmp(item->key, key) == 0)
			{
				ht_del_item(item);
				ht->items[index] = ht->deleted;
			}
		}
		i++;
	}
	ht->count--;
}
