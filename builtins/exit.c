/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 09:48:47 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/13 17:06:04 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	adjust(int stat)
{
	int	res;

	res = stat;
	if (stat < 0)
		res += 256;
	if (stat > 255)
		res -= 256;
	return (res);
}

int	exit_builtin(t_tokens *tmp, t_stat *stat_struct, bool in_fork)
{
	int		i;
	int		res;
	char	*arg;

	res = stat_struct->stat;
	if (argument_count(tmp) > 1)
		return (quit_with_error(1, "exit", "too many arguments", 1));
	tmp = find_argument(tmp);
	if (tmp)
	{
		i = 0;
		arg = tmp->token;
		while (arg[i])
		{
			if (!ft_isdigit(arg[i]) && arg[i] != '+' && arg[i] != '-')
				return (quit_with_error(1, "exit",
						"numeric argument required", 2));
			i++;
		}
		res = ft_atoi(arg);
	}
	res = adjust(res);
	if (!in_fork)
		stat_struct->must_exit = true;
	return (res);
}
