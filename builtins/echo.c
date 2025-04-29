/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:05:41 by nasargsy          #+#    #+#             */
/*   Updated: 2025/04/29 13:33:01 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(int argc, char	**argv)
{
	if (argc == 1)
		ft_putchar_fd('\n', 1);
	else if (!ft_strncmp(argv[1], "-n", 2)
		&& ft_strlen(argv[1]) == 2)
		write(1, argv[2], ft_strlen(argv[2]));
	else
		ft_printf("%s\n", argv[1]);
	return (0);
}
