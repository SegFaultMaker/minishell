/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:41:31 by armarake          #+#    #+#             */
/*   Updated: 2025/05/08 14:32:21 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	invalid_identifier(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
}

static char	*get_key(char *arg, char *equal_sign)
{
	int		i;
	int		len;
	char	*key;

	len = equal_sign - arg;
	if (len == 0)
		return (NULL);
	i = -1;
	while (i++ < len)
		if (arg[i] == ' ')
			return (NULL);
	key = malloc(len + 1);
	ft_memmove(key, arg, len);
	key[len] = '\0';
	return (key);
}

static void	process_argument(char *arg, t_hash_table *ht)
{
	char	*key;
	char	*equal_sign;

	if (!*arg)
	{
		invalid_identifier(arg);
		return ;
	}
	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		invalid_identifier(arg);
		return ;
	}
	key = get_key(arg, equal_sign);
	if (!key)
	{
		invalid_identifier(arg);
		return ;
	}
	if (!ht_insert(ht, key, equal_sign + 1))
		ft_putendl_fd("minishell: hash table: item insertation error",
			STDERR_FILENO);
	free(key);
	key = NULL;
}

static int	arg_isalnum(char *arg)
{
	if (!*arg)
		return (0);
	while (*arg)
	{
		if (!ft_isalnum(*arg))
			return (0);
		arg++;
	}
	return (1);
}

int	export(int argc, char *argv[], t_hash_table *ht)
{
	int	i;

	if (argc == 1)
		return (env(ht, 1), 0);
	i = 1;
	while (argv[i])
	{
		if (arg_isalnum(argv[i]))
		{
			i++;
			continue ;
		}
		process_argument(argv[i], ht);
		i++;
	}
	return (0);
}
