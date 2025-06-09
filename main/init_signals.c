/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:58:48 by nasargsy          #+#    #+#             */
/*   Updated: 2025/06/07 15:09:00 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	sig_handle(int sig)
{
	if (sig == SIGQUIT)
		(void)0;
	else if (sig == SIGINT)
		printf("\b\n" BLUE "→  " RESET);
}

void	init_signals(void)
{
	signal(SIGINT, &sig_handle);
	signal(SIGQUIT, &sig_handle);
}
