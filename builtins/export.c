/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:41:31 by armarake          #+#    #+#             */
/*   Updated: 2025/05/09 16:35:34 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	process_argument(char *arg, t_hash_table *ht, int mode)
{
	char	*key;
	char	*value;
	char	*key_end;
	char	*existing;

	key_end = get_key_end(arg, mode);
	if (!key_end)
		return (0);
	key = get_key(arg, key_end);
	if (!key)
		return (invalid_identifier(arg), 0);
	if (mode == JOIN_MODE)
	{
		existing = ht_search(ht, key);
		if (existing)
			value = no_free_strjoin(existing, key_end + 2);
		else
			value = key_end + 2;
	}
	else
		value = key_end + 1;
	if (!ht_insert(ht, key, value))
		ft_putendl_fd("minishell: hash table: insert error", STDERR_FILENO);
	free_key_value(key, value, existing, mode);
	return (1);
}

static int	check_argument(char *arg)
{
	int		i;

	if (!*arg)
		return (invalid_identifier(arg), 0);
	if (ft_isdigit(*arg))
		return (invalid_identifier(arg), 0);
	i = 0;
	while (arg[i])
	{
		if ((arg[i] == '+' && arg[i + 1] && arg[i + 1] == '=') || arg[i] == '=')
			break ;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (invalid_identifier(arg), 0);
		i++;
	}
	if (arg[i] == '+' && arg[i + 1] && arg[i + 1] == '=')
		return (JOIN_MODE);
	return (ADD_MODE);
}

int	export(int argc, char *argv[], t_hash_table *ht)
{
	int	i;
	int	mode;

	if (argc == 1)
		return (env(ht, 1), 0);
	i = 1;
	while (argv[i])
	{
		mode = check_argument(argv[i]);
		if (mode)
			process_argument(argv[i], ht, mode);
		i++;
	}
	return (0);
}
