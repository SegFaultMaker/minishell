/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:41:31 by armarake          #+#    #+#             */
/*   Updated: 2025/05/20 14:49:10 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	invalid_identifier(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
}

static int	process_argument(char *arg, t_hash_table *ht, int mode)
{
	char	*key;
	char	*value;
	char	*key_end;
	char	*existing;

	key_end = get_key_end(arg, mode);
	existing = NULL;
	if (!key_end)
		return (0);
	key = get_key(arg, key_end);
	if (!key)
		return (invalid_identifier(arg), 0);
	if (mode == JOIN_MODE)
	{
		existing = ht_search(ht, key);
		if (existing)
			value = ft_strjoin(existing, key_end + 2);
		else
			value = key_end + 2;
	}
	else
		value = key_end + 1;
	if (!ht_insert(ht, key, value))
		ft_putendl_fd("minishell: hash table: insert error", STDERR_FILENO);
	return (free_key_value(key, value, existing, mode), 1);
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

int	export(t_tokens *tokens, t_hash_table *ht)
{
	int	mode;

	if (!tokens)
		return (env(ht, 1), 0);
	while (tokens && !is_redir_pipe(tokens->type) && tokens->type != NEWL)
	{
		mode = check_argument(tokens->token);
		if (mode)
			process_argument(tokens->token, ht, mode);
		tokens = tokens->next;
	}
	return (0);
}
