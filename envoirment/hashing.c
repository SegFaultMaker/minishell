/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:23:23 by armarake          #+#    #+#             */
/*   Updated: 2025/05/01 12:23:43 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

static double	hash_pow(double num, int power)
{
	long	i;
	double	pow;

	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	i = 1;
	pow = 1;
	while (i <= power)
	{
		pow *= num;
		i++;
	}
	return (pow);
}

static int	do_hash(char *s, int a, int m)
{
	int		i;
	long	hash;
	int		s_len;

	i = 0;
	hash = 0;
	s_len = ft_strlen(s);
	while (s[i])
	{
		hash += (long)hash_pow(a, s_len - (i + 1)) * s[i];
		hash = hash % m;
		i++;
	}
	return ((int)hash);
}

int	ht_get_hash(char *s, int size, int attempt)
{
	int	hash_a;
	int	hash_b;

	hash_a = do_hash(s, HT_PRIME_1, size);
	hash_b = do_hash(s, HT_PRIME_2, size);
	return ((hash_a + (attempt * (hash_b + 1))) % size);
}
