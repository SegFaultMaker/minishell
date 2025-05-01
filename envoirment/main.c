/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:11:35 by armarake          #+#    #+#             */
/*   Updated: 2025/05/02 00:13:37 by armarake         ###   ########.fr       */
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

int main(int argc, char *argv[], char *env[])
{
	t_hash_table	*ht;
	char			*key;
	char			*res;
	int				i;
	int				ins_res;

	i = 0;
	ht = ht_new(env);
	if (!ht)
		return (printf("Creation error\n"), 1);
	while (env[i])
	{
		key = get_key(env[i]);
		if (!key || !get_value(env[i]))
			break ;
		if (!ht_insert(ht, key, get_value(env[i])))
		{	
			printf("Insert error\n");
			break ;
		}
		free(key);
		key = NULL;
		i++;
	}
	if (argc != 2)
		return (0);
	res = ht_search(ht, argv[1]);
	if (res)
		printf("Found value \"%s\" with key \"%s\"\n\n", res, argv[1]);
	else
		return (printf("Nothing found\n"), 0);
	ht_delete(ht, argv[1]);
	printf("Deleted \"%s\"\n\n", argv[1]);
	ins_res = ht_insert(ht, argv[1], "DOUBLE NIGGER");
	if (!ins_res)
		printf("Allocation error\n\n");
	else if (ins_res == 1)
		printf("Added new key \"%s\" with value \"%s\"\n\n", argv[1], "DOUBLE NIGGER");
	else if (ins_res == 2)
		printf("Value of \"%s\" updated to: %s\n\n", argv[1], "DOUBLE NIGGER");
	res = ht_search(ht, argv[1]);
	if (res)
		printf("Found value \"%s\" with key \"%s\"\n", res, argv[1]);
	else
		printf("Nothing found\n");
	del_hash_table(ht);
	return (0);
}