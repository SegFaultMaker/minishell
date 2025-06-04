/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:33:00 by armarake          #+#    #+#             */
/*   Updated: 2025/06/04 18:57:16 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static t_commands	*last_command(t_commands *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

static void	command_add_back(t_commands **cmd, t_commands *new)
{
	t_commands	*temp;

	if (!cmd || !new)
		return ;
	if (!*cmd)
		*cmd = new;
	else
	{
		temp = *cmd;
		temp = last_command(temp);
		temp->next = new;
	}
}

static void	add_new_command(t_commands **commands, t_tokens *tokens)
{
	t_commands	*new;

	new = malloc(sizeof(t_commands));
	new->cmd = tokens->token;
	new->args = tokens_to_strings(tokens);
	new->input = STDIN_FILENO;
	new->output = STDOUT_FILENO;
	new->next = NULL;
	command_add_back(commands, new);
}

t_commands	*tokens_to_commands(t_tokens *tokens)
{
	t_commands	*commands;

	commands = NULL;
	while (tokens->type != NEWL)
	{
		if (tokens->type == COMMAND)
			add_new_command(&commands, tokens);
		tokens = tokens->next;
	}
	return (commands);
}
