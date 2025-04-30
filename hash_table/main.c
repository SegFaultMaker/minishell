/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:11:35 by armarake          #+#    #+#             */
/*   Updated: 2025/04/30 18:40:52 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"
#include <string.h>

char *get_value(char *env_var)
{
	int	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	return (env_var + i + 1);
}

char *get_key(char *env_var)
{
	const char *equal_sign = strchr(env_var, '=');
    if (!equal_sign)
        return NULL;

    size_t key_len = equal_sign - env_var;
    char *key = malloc(key_len + 1);
    if (!key)
        return NULL;

    strncpy(key, env_var, key_len);
    key[key_len] = '\0';

    return key;
}

int main(int argc, char *argv[], char *env[]) // compile using: cc -lm ../libft/*c *.c
{
	t_hash_table	*ht;
	char			*key;
	int				i;

	i = 0;
	ht = ht_new();
	while (env[i])
	{
		char *key = get_key(env[i]);
		if (!key || !get_value(env[i]))
			break ;
		ht_insert(ht, key, get_value(env[i]));
		free(key);
		key = NULL;
		i++;
	}
	i = 0;
	while (i < ht->size)
	{
		if (ht->items[i] != NULL && ht->items[i] != ht->deleted)
			ft_printf("%s=%s\n", ht->items[i]->key, ht->items[i]->value);
		i++;
	}
	del_hash_table(ht);
	return (0);
}