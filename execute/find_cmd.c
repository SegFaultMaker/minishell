/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:37:18 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/16 16:44:52 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	check_access(char *cmd)
{
	if (*cmd != '/' && (cmd[0] != '.' && cmd[1] != '/'))
	{
		if (access(cmd, F_OK))
		{
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd("command not found", STDERR_FILENO);
			return (errno);
		}
	}
	else if (access(cmd, F_OK))
		return (quit_with_error(1, cmd, errno));
	if (access(cmd, X_OK))
		return (quit_with_error(1, cmd, errno));
	return (0);
}

static char	*get_fullpath(char *cmd, char **paths)
{
	char	*temp;
	char	*temp_cmd;
	char	*fullpath;
	int		i;

	fullpath = NULL;
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		temp_cmd = ft_strjoin(temp, cmd);
		free(temp);
		if (access(temp_cmd, F_OK) == 0)
		{
			fullpath = temp_cmd;
			break ;
		}
		free(temp_cmd);
	}
	if (!fullpath)
		return (cmd);
	free_matrix(paths);
	return (fullpath);
}

char	*find_cmd(char *cmd, char **envp)
{
	char	**paths;
	char	*fullpath;
	char	*env_variable;
	int		i;

	fullpath = NULL;
	if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
	{
		if (check_access(cmd))
			return (NULL);
		return (cmd);
	}
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			env_variable = envp[i];
	}
	env_variable = ft_strchr(env_variable, '/');
	paths = ft_split(env_variable, ':');
	if (!paths)
		return (NULL);
	fullpath = get_fullpath(cmd, paths);
	if (check_access(fullpath))
		return (NULL);
	return (fullpath);
}
