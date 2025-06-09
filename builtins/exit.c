/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 09:48:47 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/09 13:13:54 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	adjust(int stat)
{
	int res;

	res = stat;
	if (stat < 0)
		res += 256;
	if (stat > 255)
		res -= 256;
	return (res);
}

int	exit_builtin(t_tokens *tmp, int prev_stat)
{
	int		res;
	char	*N;
	int		i;

	res = prev_stat;
	if (tmp->next->type == ARGUMENT)
		return (quit_with_error(1, "exit", "too many arguments", 1));
	if (tmp->type == ARGUMENT)
	{
		i = 0;
		N = tmp->token;
		while (N[i])
		{
			if (!ft_isdigit(N[i]))
				return (quit_with_error(1, "exit",
						"numeric argument required", 1));
			i++;
		}
		res = ft_atoi(N);
	}
	res = adjust(res);
	return (res);
}
