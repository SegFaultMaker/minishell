/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:11:35 by armarake          #+#    #+#             */
/*   Updated: 2025/05/03 23:19:43 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envoirment.h"

int	main(int argc, char *argv[], char *env[])
{
	int				i;
	char			**result;
	t_hash_table	*ht;

	(void)argc;
	(void)argv;
	ht = init_envoirment(env);
	if (!ht)
		return (1);
	result = ht_to_strings(ht);
	i = 0;
	while (result[i])
	{
		printf("%s\n", result[i]);
		i++;
	}
	free_result(result);
	del_hash_table(ht);
	return (0);
}
