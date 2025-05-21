/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:19:40 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/21 19:21:38 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	validate(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$' && ft_isalpha(str[i + 1]))
			return (i);
	return (INT_MIN);
}

static char	*find_var(char *str, t_hash_table *env)
{
	int		i;
	char	*var;
	char	*res;

	i = 0;
	while (str[i] && str[i] != '\"')
		i++;
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (NULL);
	var[i] = '\0';
	i = 0;
	while (str[i] && str[i] != '\"')
	{
		var[i] = str[i];
		i++;
	}
	res = ht_search(env, var);
	free(var);
	return (res);
}

static void	replace(t_tokens **tokens, char *var, int doll_pos)
{
	int		i;
	int		len;
	char	*new_token;

	if (!var)
	{
		new_token = ft_substr((*tokens)->token, doll_pos, doll_pos);
		free((*tokens)->token);
		(*tokens)->token = new_token;
		return ;
	}
	len = doll_pos + ft_strlen(var);
	new_token = malloc(len + 1);
	i = -1;
	while (++i < doll_pos)
		new_token[i] = (*tokens)->token[i];
	ft_memmove(new_token + i, var, ft_strlen(var));
	new_token[len] = '\0';
	free((*tokens)->token);
	(*tokens)->token = new_token;
}

static void	replace_to_var(t_tokens **tokens, t_hash_table *env, int doll_pos)
{
	char	*var;

	var = find_var((*tokens)->token + doll_pos + 1, env);
	replace(tokens, var, doll_pos);
}

void	env_vars(t_tokens **tokens, t_hash_table *env)
{
	int			dollar_position;
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp->type != NEWL)
	{
		dollar_position = validate(tmp->token);
		if (dollar_position != INT_MIN)
			replace_to_var(&tmp, env, dollar_position);
		tmp = tmp->next;
	}
}
