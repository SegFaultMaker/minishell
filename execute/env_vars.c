/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:19:40 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/22 18:00:35 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	find_dollar(char *str)
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
	while (str[i] && str[i] != '\"' && str[i] != '\'')
		i++;
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (NULL);
	var[i] = '\0';
	i = 0;
	while (str[i] && str[i] != '\"' && str[i] != '\'')
	{
		var[i] = str[i];
		i++;
	}
	res = ht_search(env, var);
	free(var);
	return (res);
}

static int	calculate_len(char *old, int doll_pos, char *env_var, int *flag)
{
	int	i;
	int	len;

	i = 0;
	*flag = 0;
	len = doll_pos + ft_strlen(env_var);
	while (old[i] && old[i] != '\"' && old[i] != '\'')
		i++;
	if (old[i] == '\0' || (old[i] != '\"' && old[i] != '\''))
		return (len);
	*flag = 1;
	while (old[i])
	{
		i++;
		len++;
	}
	return (len);
}

static void	replace_to_var(t_tokens **tokens, t_hash_table *env, int doll_pos)
{
	int		i;
	int		len;
	int		flag;
	char	*env_var;
	char	*new_token;

	env_var = find_var((*tokens)->token + doll_pos + 1, env);
	if (!env_var)
	{
		new_token = ft_substr((*tokens)->token, 0, doll_pos);
		free((*tokens)->token);
		(*tokens)->token = new_token;
		return ;
	}
	len = calculate_len((*tokens)->token, doll_pos, env_var, &flag);
	new_token = malloc(len + 1);
	i = -1;
	while (++i < doll_pos)
		new_token[i] = (*tokens)->token[i];
	ft_memmove(new_token + i, env_var, ft_strlen(env_var));
	if (flag)
		add_the_rest(tokens, doll_pos, &new_token, i + ft_strlen(env_var));
	new_token[len] = '\0';
	free((*tokens)->token);
	(*tokens)->token = new_token;
}

void	env_vars(t_tokens **tokens, t_hash_table *env)
{
	int			dollar_position;
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp->type != NEWL)
	{
		dollar_position = find_dollar(tmp->token);
		if (dollar_position != INT_MIN)
			replace_to_var(&tmp, env, dollar_position);
		tmp = tmp->next;
	}
}
