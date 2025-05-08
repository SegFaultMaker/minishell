/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:46:56 by armarake          #+#    #+#             */
/*   Updated: 2025/05/08 14:22:45 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include "../envoirment/environment.h"

//			enviroment
int	export(int argc, char *argv[], t_hash_table *ht);
int	env(t_hash_table *ht, int mode);
int	unset(char *argv[], t_hash_table *ht);

//			other
int	cd(char *path);
int	echo(int argc, char	**argv);
int	pwd(void);

#endif