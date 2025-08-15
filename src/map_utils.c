/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-14 12:30:01 by dashvydk          #+#    #+#             */
/*   Updated: 2025-08-14 12:30:01 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// fd = open(filename, O_RDONLY);

// This opens the file in read-only mode
// Returns a file descriptor (fd):
// If successful: returns a positive number (3 or higher, because 0, 1, and 2 are reserved for stdin, stdout, and stderr)
// If failed: returns -1
// if (fd < 0)

// Checks if file opening failed
// We return NULL if we couldn't open the file
// map_str = ft_strdup("");

// Creates an empty string to start with
// We'll append each line to this string

char	*read_file_to_str(char *filename)
{
	int		fd;
	char	*line;
	char	*tmp;
	char	*map_str;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map_str = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = map_str;
		map_str = ft_strjoin(map_str, line);
		free(tmp);
		free(line);
	}
	close(fd);
	return (map_str);
}
// Convert the map from a single string to a 2D array
// Verify that all rows have the same length (map is rectangular)

char	**split_to_2d_array(char *map_str)
{
	char	**map;
	int		i;

	if (!map_str)
		return (NULL);
	map = ft_split(map_str, '\n');
	if (!map)
		return (NULL);
	return (map);
}


int	is_map_rectangular(char **map)
{
	int	len;
	int	i;

	if (!map || !map[0])
		return (0);
	len = ft_strlen(map[0]);
	i = 1;
	while (map[i])
	{
		if (ft_strlen(map[i]) != len)
			return (0);
		i++;
	}
	return (1);
}
