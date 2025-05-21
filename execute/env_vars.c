/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <nasargsy@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:19:40 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/21 16:11:25 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	validate(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && ft_isalpha(str[i + 1]))
			return (1);
	}
	return (0);
}

static char	*find_var(char *str, t_hash_table *env)
{
	int		i;
	char	*var;
	char	*res;

	i = 0;
	while (str[i] && str[i] != '\"')
		i++;
	var = malloc(sizeof(char) * i + 1);
	if (!var)
		return (NULL);
	var[i] = 0;
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
static void	replace(char **str, char *var)
{
	char	*tmp;
	int		i;

	tmp = *str;
	i = 0;
	while (tmp[i] != '$')
		i++;
	tmp = malloc(i + 1);
	if (!tmp)
		return ;
	tmp[i] = 0;
	while (i--)
		tmp[i] = (*str)[i];
	free(*(str));
	*str = ft_strjoin(tmp, var);
}

static void	replace_to_var(char *str, t_hash_table *env)
{
	int		i;
	char	*var;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			var = find_var(str + i + 1, env);
			replace(&str, var);
			break ;
		}
	}
}

void	env_vars(t_tokens *tmp, t_hash_table *env)
{
	while (tmp->type != NEWL)
	{
		if (validate(tmp->token))
			replace_to_var(tmp->token, env);
		tmp = tmp->next;
	}
}
