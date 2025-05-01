/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:34:21 by armarake          #+#    #+#             */
/*   Updated: 2025/05/01 15:58:21 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# include "../libft/libft.h"
# include <stdio.h>

# define HT_PRIME_1 151
# define HT_PRIME_2 163

typedef struct s_ht_item {
	char	*key;
	char	*value;
}	t_ht_item;

typedef struct s_hash_table {
	int			size;
	int			count;
	t_ht_item	*deleted;
	t_ht_item	**items;
}	t_hash_table;

//					create
t_ht_item		*ht_new_item(char *k, char *v);
t_hash_table	*ht_new(char *env[]);

//					delete
void			ht_del_item(t_ht_item *item);
void			del_hash_table(t_hash_table *ht);

//					hashing
int				ht_get_hash(char *s, int size, int attempt);

//					hash table operations
int 			ht_insert(t_hash_table *ht, char *key, char *value);
char			*ht_search(t_hash_table *ht, char *key);
void 			ht_delete(t_hash_table *ht, char *key);

#endif