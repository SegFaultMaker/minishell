/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 09:48:47 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/19 17:26:53 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

static int	handle_error(t_stat *stat_struct, int err)
{
	if (err)
		ft_putendl_fd("exit", STDOUT_FILENO);
	stat_struct->must_exit = true;
	return (quit_with_error(1, "exit",
			"numeric argument required", 2));
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
		i = -1;
		arg = tmp->token;
		if (!arg[0] || ((arg[0] == '+' || arg[0] == '-') && arg[1] == arg[0]))
			return (handle_error(stat_struct, 1));
		while (arg[++i])
			if (!ft_isdigit(arg[i]) && arg[i] != '+' && arg[i] != '-')
				return (handle_error(stat_struct, 0));
		res = ft_atoi(arg);
	}
	if (!in_fork)
		stat_struct->must_exit = true;
	ft_putendl_fd("exit", STDOUT_FILENO);
	return ((int)((unsigned char)res));
}
