/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 09:48:47 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/17 14:09:05 by nasargsy         ###   ########.fr       */
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

static int	check_args(t_tokens *tmp)
{
	int	all_num;
	int	i;

	all_num = 1;
	while (tmp->type != NEWL)
	{
		i = -1;
		while (tmp->token[++i])
		{
			if (!ft_isdigit(tmp->token[i]))
				all_num = 2;
		}
		tmp = tmp->next;
	}
	return (quit_with_error(1, "exit", "too many arguments", all_num));
}

int	exit_builtin(t_tokens *tmp, t_stat *stat_struct, bool in_fork)
{
	int		i;
	int		res;
	char	*arg;

	res = stat_struct->stat;
	if (argument_count(tmp) > 1)
		return (check_args(tmp));
	tmp = find_argument(tmp);
	if (tmp)
	{
		i = 0;
		arg = tmp->token;
		if (!arg[0] || ((arg[0] == '+' || arg[0] == '-') && arg[1] == arg[0]))
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			stat_struct->must_exit = true;
			return (quit_with_error(1, "exit",
						"numeric argument required", 2));
		}
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
	{	
		ft_putendl_fd("exit", STDOUT_FILENO);
		stat_struct->must_exit = true;
	}
	return (res);
}
