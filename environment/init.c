/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:41:45 by armarake          #+#    #+#             */
/*   Updated: 2025/05/04 14:36:53 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static char	*get_value(char *env_var)
{
	return (ft_strchr(env_var, '=') + 1);
}

static char	*get_key(char *env_var)
{
	size_t	len;
	char	*key;
	char	*equal_sign;

	equal_sign = ft_strchr(env_var, '=');
	if (!equal_sign)
		return (NULL);
	len = equal_sign - env_var;
	key = malloc(len + 1);
	if (!key)
		return (NULL);
	ft_memmove(key, env_var, len);
	key[len] = '\0';
	return (key);
}

t_hash_table	*init_environment(char *env[])
{
	int				i;
	char			*key;
	t_hash_table	*environment_ht;

	environment_ht = ht_new(HT_DEFAULT_BASE_SIZE);
	if (!environment_ht)
		return (printf("Creation error\n"), NULL);
	i = -1;
	while (env[++i])
	{
		key = get_key(env[i]);
		if (!key)
		{
			printf("Envoirment variable parsing error\n");
			return (del_hash_table(environment_ht), free(key), NULL);
		}
		if (!ht_insert(environment_ht, key, get_value(env[i])))
		{
			printf("Item insertation error\n");
			return (del_hash_table(environment_ht), free(key), NULL);
		}
		free(key);
		key = NULL;
	}
	return (environment_ht);
}
