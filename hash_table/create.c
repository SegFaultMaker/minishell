/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:21:37 by armarake          #+#    #+#             */
/*   Updated: 2025/04/30 18:42:25 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

t_ht_item	*ht_new_item(char *k, char *v)
{
	t_ht_item *item = malloc(sizeof(t_ht_item));
	item->key = ft_strdup(k);
	item->value = ft_strdup(v);
	return (item);
}

static t_ht_item	*ht_deleted(void)
{
	t_ht_item *deleted = malloc(sizeof(t_ht_item));
	deleted->key = NULL;
	deleted->value = NULL;
	return (deleted);
}

t_hash_table	*ht_new(void)
{
	t_hash_table	*ht = malloc(sizeof(t_hash_table));

	ht->size = 53;
	ht->count = 0;
	ht->deleted = ht_deleted();
	ht->items = ft_calloc((size_t)ht->size, sizeof(t_ht_item *));
	return (ht);
}
