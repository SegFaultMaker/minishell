/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <nasargsy@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:28:29 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/02 19:02:23 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_commands(t_commands **commands)
{
	t_commands	*tmp;

	tmp = *commands;
	while (tmp)
	{
		free_tokens(&(tmp->first));
		if (tmp->second)
			free_tokens(&(tmp->second));
		tmp = tmp->next;
	}
	free(*commands);
}
