/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:21:37 by armarake          #+#    #+#             */
/*   Updated: 2025/05/02 00:13:53 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

t_ht_item	*ht_new_item(char *k, char *v)
{
	t_ht_item *item = malloc(sizeof(t_ht_item));
	item->key = ft_strdup(k);
	item->value = ft_strdup(v);
	if (!item->key || !item->value)
		return (NULL);
	return (item);
}

static t_ht_item	*ht_deleted(void)
{
	t_ht_item *deleted = malloc(sizeof(t_ht_item));
	if (!deleted)
		return (NULL);
	deleted->key = NULL;
	deleted->value = NULL;
	return (deleted);
}

static void	set_nulls(t_hash_table	*ht)
{
	int	i;

	i = 0;
	while (i < ht->size)
	{
		ht->items[i] = NULL;
		i++;
	}
}

static int env_len(char *env[])
{
	int	len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

t_hash_table	*ht_new(char *env[])
{
	t_hash_table	*ht;
	
	ht = malloc(sizeof(t_hash_table));
	if (!ht)
		return (NULL);
	ht->size = env_len(env) * 2;
	ht->count = 0;
	ht->deleted = ht_deleted();
	if (!ht->deleted)
		return (NULL);
	ht->items = malloc(ht->size * sizeof(t_ht_item *));
	if (!ht->items)
		return (NULL);
	set_nulls(ht);
	return (ht);
}
