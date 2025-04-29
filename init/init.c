/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:58:48 by nasargsy          #+#    #+#             */
/*   Updated: 2025/04/29 15:08:36 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	sig_handle(int sig)
{
	if (sig == SIGQUIT)
		(void)0;
	else if (sig == SIGINT)
		printf("TODO THIS SHIT\n");
}

void	init_signals(void)
{
	signal(SIGINT, &sig_handle);
	signal(SIGQUIT, &sig_handle);
}
