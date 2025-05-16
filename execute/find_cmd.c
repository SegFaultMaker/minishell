/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:37:18 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/16 13:51:29 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	check_access(char *cmd)
{
	if (access(cmd, F_OK))
		return (quit_with_error(0, cmd, errno));
	else if (access(cmd, X_OK))
		return (quit_with_error(0, cmd, errno));
	return (0);
}

static char	*get_fullpath(char *cmd, char **paths)
{
	char	*temp;
	char	*temp_cmd;
	char	*fullpath;

	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		if (!temp)
			return (NULL);
		temp_cmd = ft_strjoin(temp, cmd);
		if (access(temp_cmd, F_OK) == 0)
		{
			fullpath = temp_cmd;
			break ;
		}
		free(temp_cmd);
		paths++;
	}
	return (fullpath);
}

char	*find_cmd(char *cmd, char **envp)
{
	char	**paths;
	char	*fullpath;
	char	*env_variable;

	if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
	{
		if (check_access(cmd))
			return (NULL);
		else
			return (cmd);
	}
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			env_variable = *envp;
		envp++;
	}
	env_variable = ft_strchr(env_variable, '/');
	paths = ft_split(env_variable, ':');
	if (!paths)
		return (NULL);
	fullpath = get_fullpath(cmd, paths);
//	free_matrix(&paths);
	if (check_access(fullpath))
		return (NULL);
	return (fullpath);
}
