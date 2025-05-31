/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_len_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:34:19 by armarake          #+#    #+#             */
/*   Updated: 2025/05/31 17:11:05 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	dollar_question_mark_len(int *i, int stat)
{
	int		len;
	char	*status;

	status = ft_itoa(stat);
	len = safe_strlen(status);
	free(status);
	*i += 2;
	return (len);
}

int	env_var_len(char *token, int *i, t_hash_table *env)
{
	int		len;
	char	*env_var;

	env_var = find_var(token + *i + 1, env);
	len = safe_strlen(env_var);
	(*i)++;
	while (token[*i] && (ft_isalnum(token[*i]) || token[*i] == '_'))
		(*i)++;
	return (len);
}

int	initialize_vars(int *i, int *quote, int *final_len, char *token)
{
	*i = 0;
	*quote = 0;
	*final_len = 0;
	return (safe_strlen(token));
}
