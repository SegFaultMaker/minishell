/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <nasargsy@student.42yerevan.am>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:37:18 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/15 16:55:37 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	check_access(char *cmd, int regime)
{
	if (regime == 1)
	{
		if (access(cmd, F_OK) < 0)
			return (quit_with_error(" command not found", -1));
		else if (access(cmd, X_OK) < 0)
			return (handle_access(cmd), errno);
	}
	else
	{
		if (access(cmd, F_OK) < 0)
			return (handle_access(cmd), errno);
		else if (access(cmd, X_OK) < 0)
			return (handle_access(cmd), errno);
	}
	return (1);
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
		if (check_access(cmd, 1) < 0)
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
	if (check_access(fullpath, 0) < 0)
		return (NULL);
	return (fullpath);
}
