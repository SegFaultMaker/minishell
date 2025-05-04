/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:41:31 by armarake          #+#    #+#             */
/*   Updated: 2025/05/04 20:07:03 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*get_key(char *arg, char *equal_sign)
{
	int		i;
	int		len;
	char	*key;

	len = equal_sign - arg;
	i = -1;
	while (i++ < len)
		if (arg[i] == ' ')
			return (NULL);
	key = malloc(len + 1);
	ft_memmove(key, arg, len);
	key[len] = '\0';
	return (key);
}

static int	process_argument(char *arg, t_hash_table *ht)
{
	char	*key;
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (1);
	key = get_key(arg, equal_sign);
	if (!key)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("`: not a valid identifier\n", 2);
		return (0);
	}
	if (!ht_insert(ht, key, equal_sign + 1))
		printf("Item insertation error\n");
	free(key);
	key = NULL;
	return (1);
}

int	export(int argc, char *argv[], t_hash_table *ht)
{
	int	i;

	if (argc == 1)
		return (env(ht), 1);
	i = 1;
	while (argv[i])
	{
		process_argument(argv[i], ht);
		i++;
	}
	return (0);
}
