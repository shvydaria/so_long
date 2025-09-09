/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-24 12:24:36 by dashvydk          #+#    #+#             */
/*   Updated: 2025-04-24 12:24:36 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*append_buffer(char *buffer, char *small_buffer)
{
	char	*temp;

	temp = gnl_strjoin(buffer, small_buffer);
	free(buffer);
	buffer = NULL;
	return (temp);
}

char	*read_from_file(char *buffer, int fd)
{
	int		bytes_read;
	char	*small_buffer;

	small_buffer = gnl_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (small_buffer == NULL)
		return (NULL);
	if (!buffer)
		buffer = gnl_calloc(1, sizeof(char));
	if (buffer == NULL)
		return (free(small_buffer), NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, small_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(small_buffer), NULL);
		small_buffer[bytes_read] = '\0';
		buffer = append_buffer(buffer, small_buffer);
		if (buffer == NULL)
			return (NULL);
		if (gnl_strchr(buffer, '\n'))
			break ;
	}
	free(small_buffer);
	return (buffer);
}

char	*extract_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = gnl_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*update_buff(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = gnl_calloc((gnl_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	buffer = NULL;
	return (line);
}

//! main function responsible for reading data from the fd that fills
// the buffer to with the scooped content until atleast one ‘\n’
// new line character is found.
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = read_from_file(buffer, fd);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = update_buff(buffer);
	return (line);
}
