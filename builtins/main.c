/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:13:00 by armarake          #+#    #+#             */
/*   Updated: 2025/05/08 16:12:05 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_hash_table	*ht;

	ht = init_environment(envp);
	if (export(argc, argv, ht))
		printf("Export error\n");
	printf("\n\n");
	env(ht, 0);
	del_hash_table(ht);
	return (0);
}
