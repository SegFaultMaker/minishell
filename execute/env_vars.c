/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:19:40 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/25 22:00:45 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	find_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$' && str[i + 1])
			return (i);
	return (INT_MIN);
}

static char	*find_var(char *str, t_hash_table *env)
{
	int		i;
	char	*var;
	char	*res;

	i = 0;
	while (str[i] && str[i] != '\"' && str[i] != '\''
		&& str[i] != '+' && str[i] != '=' && str[i] != '$')
		i++;
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (NULL);
	var[i] = '\0';
	i = 0;
	while (str[i] && str[i] != '\"' && str[i] != '\''
		&& str[i] != '+' && str[i] != '=' && str[i] != '$')
	{
		var[i] = str[i];
		i++;
	}
	res = ht_search(env, var);
	free(var);
	return (res);
}

static void	dollar_question_mark(t_tokens **tokens, int doll_pos)
{
	int		i;
	int		j;
	int		len;
	char	*status_code;
	char	*new_token;

	status_code = ft_itoa(errno);
	len = safe_strlen((*tokens)->token) - 2 + safe_strlen(status_code);
	new_token = malloc(len + 1);
	i = -1;
	while (++i < doll_pos)
		new_token[i] = (*tokens)->token[i];
	ft_memmove(new_token + i, status_code, safe_strlen(status_code));
	j = i;
	i += 2;
	ft_memmove(new_token + j + safe_strlen(status_code),
		(*tokens)->token + i, the_rest_len((*tokens)->token, i));
	new_token[len] = '\0';
	free((*tokens)->token);
	free(status_code);
	(*tokens)->token = new_token;
}

static void	replace_to_var(t_tokens **tokens, t_hash_table *env, int doll_pos)
{
	int		i;
	int		len;
	int		flag;
	char	*env_var;
	char	*new_token;

	if ((*tokens)->token[doll_pos + 1] == '?')
	{
		dollar_question_mark(tokens, doll_pos);
		return ;
	}
	env_var = find_var((*tokens)->token + doll_pos + 1, env);
	len = calculate_len((*tokens)->token, doll_pos, env_var, &flag);
	new_token = malloc(len + 1);
	i = -1;
	while (++i < doll_pos)
		new_token[i] = (*tokens)->token[i];
	ft_memmove(new_token + i, env_var, safe_strlen(env_var));
	if (flag)
		add_the_rest(tokens, doll_pos, &new_token, i + safe_strlen(env_var));
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
		while (1)
		{
			dollar_position = find_dollar(tmp->token);
			if (dollar_position != INT_MIN)
				replace_to_var(&tmp, env, dollar_position);
			else
				break ;
		}
		tmp = tmp->next;
	}
}
