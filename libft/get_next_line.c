/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:47:20 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/10 11:34:14 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = (char *) malloc(sizeof(char) *(i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*get_after_new_line(char *stash)
{
	char	*remaining_data;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	remaining_data = (char *)malloc(sizeof(char) *(ft_strlen(stash)- i + 1));
	if (!remaining_data)
	{
		free(stash);
		return (NULL);
	}
	i++;
	j = 0;
	while (stash[i])
		remaining_data[j++] = stash[i++];
	remaining_data[j] = '\0';
	free (stash);
	return (remaining_data);
}

static char	*free_and_null(char *a, char *b)
{
	free(a);
	free(b);
	return (NULL);
}

static char	*read_and_get_stash(int fd, char *stash)
{
	char	*buffer;
	int		read_bytes;

	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(stash, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free_and_null(buffer, stash));
		buffer[read_bytes] = '\0';
		stash = ft_gnl_strjoin(stash, buffer);
		if (!stash)
			return (free_and_null(buffer, NULL));
	}
	free (buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_get_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = get_after_new_line(stash);
	return (line);
}
