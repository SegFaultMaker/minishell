/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:58:48 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/17 14:42:10 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	sig_handle(int sig)
{
	if (sig == SIGQUIT)
		(void)0;
	else if (sig == SIGINT)
		printf("\n" BLUE "→  " RESET);
}

void	sig_handle_exec(int sig)
{
	if (sig == SIGQUIT)
		printf("Quit (core dumped)\n");
	else
		printf("\n");
}

void	init_signals(void)
{
	signal(SIGINT, &sig_handle);
	signal(SIGQUIT, SIG_IGN);
}
