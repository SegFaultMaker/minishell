/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:09:12 by nasargsy          #+#    #+#             */
/*   Updated: 2025/04/29 16:11:53 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	line = readline("minishell $ ");
	printf("Line: %s\n", line);
	t_tokens *tokens = parser(line);
	t_tokens *tmp = tokens;
	int	i = 1;
	while (tmp)
	{
		printf("Token %d: %s\n", i, tmp->token);
		i++;
		tmp = tmp->next;
	}
	free_tokens(&tokens);
	return (0);
}
