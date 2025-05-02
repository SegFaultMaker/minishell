/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:42:02 by armarake          #+#    #+#             */
/*   Updated: 2025/05/02 14:03:14 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

int	ht_insert(t_hash_table *ht, char *key, char *value)
{
	int			i;
	int			load;
	int			index;
	t_ht_item	*item;
	t_ht_item	*cur_item;

	load = ht->count * 100 / ht->size;
	if (load > 70)
		ht_resize_up(ht);
	item = ht_new_item(key, value);
	if (!item)
		return (0);
	i = 0;
	while (i < ht->size)
	{
		index = ht_get_hash(item->key, ht->size, i);
		cur_item = ht->items[index];
		if (cur_item == NULL || cur_item == ht->deleted)
			break ;
		if (ft_strcmp(cur_item->key, key) == 0)
		{
			free(cur_item->value);
			cur_item->value = ft_strdup(value);
			ht_del_item(item);
			return (2);
		}
		i++;
	}
	ht->items[index] = item;
	ht->count++;
	return (1);
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
	int			load;
	int			index;
	t_ht_item	*item;

	load = ht->count * 100 / ht->size;
	if (load < 10)
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
