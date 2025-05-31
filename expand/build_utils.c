/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:41:34 by armarake          #+#    #+#             */
/*   Updated: 2025/05/31 17:10:46 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	handle_dollar_question_mark(char **result, int *i, int *j, int stat)
{
	char	*status;
	int		status_len;

	status = ft_itoa(stat);
	status_len = safe_strlen(status);
	ft_memmove((*result) + *j, status, status_len);
	*j += status_len;
	free(status);
	*i += 2;
}

void	handle_env_var(char **result, t_data *data, t_hash_table *env)
{
	int		env_var_len;
	char	*env_var;

	env_var = find_var(data->token + data->i + 1, env);
	env_var_len = safe_strlen(env_var);
	ft_memmove(*result + data->j, env_var, env_var_len);
	data->j += env_var_len;
	data->i++;
	while (data->token[data->i] && (ft_isalnum(data->token[data->i])
			|| data->token[data->i] == '_'))
		data->i++;
}

t_data	*init_data(char *token, int stat)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->i = 0;
	data->j = 0;
	data->len = safe_strlen(token);
	data->stat = stat;
	data->quote = 0;
	data->token = ft_strdup(token);
	return (data);
}
