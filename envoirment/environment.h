/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:30:06 by armarake          #+#    #+#             */
/*   Updated: 2025/05/04 19:01:45 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "../libft/libft.h"
# include <stdio.h>

# define HT_PRIME_1 151
# define HT_PRIME_2 47

# define HT_DEFAULT_BASE_SIZE 50

# define INSERT_FAILURE 0
# define INSERT_SUCCESS 1
# define UPDATE_SUCCESS 2

typedef struct s_ht_item
{
	char	*key;
	char	*value;
}	t_ht_item;

typedef struct s_hash_table
{
	int			size;
	int			base_size;
	int			count;
	t_ht_item	*deleted;
	t_ht_item	**items;
}	t_hash_table;

//					create
t_ht_item		*ht_new_item(char *k, char *v);
t_hash_table	*ht_new(int base_size);

//					delete
void			ht_del_item(t_ht_item *item);
void			del_hash_table(t_hash_table *ht);

//					hashing
int				ht_get_hash(char *s, int size, int attempt);

//					operations
int				ht_insert(t_hash_table *ht, char *key, char *value);
char			*ht_search(t_hash_table *ht, char *key);
void			ht_delete(t_hash_table *ht, char *key);

//					resizing
void			ht_resize_up(t_hash_table *ht);
void			ht_resize_down(t_hash_table *ht);

//					utils
int				next_prime(int nb);
int				ht_load(t_hash_table *ht);

//					init
t_hash_table	*init_environment(char *env[]);

//					to strings
char			**ht_to_strings(t_hash_table *ht);
void			free_result(char **array);

#endif