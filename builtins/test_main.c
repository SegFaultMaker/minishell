/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:11:35 by armarake          #+#    #+#             */
/*   Updated: 2025/05/04 20:07:39 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_hash_table	*ht;

	ht = init_environment(envp);
	if (!ht)
		return (1);
	if (export(argc, argv, ht))
		printf("Export error\n");
	env(ht);
	del_hash_table(ht);
	return (0);
}
