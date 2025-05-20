/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasargsy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:57:29 by nasargsy          #+#    #+#             */
/*   Updated: 2025/05/20 15:42:29 by nasargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_from_file(int fd, char *res)
{
	char	*buf;
	int		rb;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	rb = 1;
	while (!ft_strchr(res, '\n') && rb > 0)
	{
		rb = read(fd, buf, BUFFER_SIZE);
		if (rb < 0)
		{
			free(buf);
			free(res);
			return (NULL);
		}
		buf[rb] = '\0';
		res = ft_strjoin(res, buf);
	}
	free(buf);
	return (res);
}

static char	*extract_line(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer || !*buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_substr(buffer, 0, i + 1);
	return (line);
}

static char	*update_buffer(char	*buffer)
{
	char	*res;
	int		i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	res = ft_substr(buffer, i + 1, ft_strlen(buffer) - i);
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer[65535];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = read_from_file(fd, buffer[fd]);
	line = extract_line(buffer[fd]);
	buffer[fd] = update_buffer(buffer[fd]);
	return (line);
}
