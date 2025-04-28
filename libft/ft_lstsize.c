/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:05:47 by nasargsy          #+#    #+#             */
/*   Updated: 2025/01/11 12:31:30 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		n;
	t_list	*temp;

	if (!lst)
		return (0);
	n = 1;
	temp = lst;
	while (temp->next != NULL)
	{
		n++;
		temp = temp->next;
	}
	return (n);
}
