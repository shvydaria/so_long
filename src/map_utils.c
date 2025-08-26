/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshvydka <dshvydka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:30:01 by dashvydk          #+#    #+#             */
/*   Updated: 2025/08/26 19:15:01 by dshvydka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
// (3 or higher, because 0, 1, and 2 are reserved for stdin, stdout, and stderr)
// if failed: returns -1
// if (fd < 0)
// map_str = ft_strdup("");
// creates an empty string to start with
// append each line to this string

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

	if (!map_str)
		return (NULL);
	map = ft_split(map_str, '\n');
	if (!map)
		return (NULL);
	return (map);
}

int	is_map_rectangular(char **map)
{
	size_t len;
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
char	*ft_strarr_join(char **arr)
{
    char	*result;
    size_t	total_len;
    int		i;

    if (!arr || !arr[0])
        return (NULL);
    total_len = 0;
    i = 0;
    while (arr[i])
    {
        total_len += ft_strlen(arr[i]) + 1; // +1 for newline
        i++;
    }
    result = (char *)malloc(sizeof(char) * (total_len + 1));
    if (!result)
        return (NULL);
    result[0] = '\0';
    i = 0;
    while (arr[i])
    {
        ft_strlcat(result, arr[i], total_len + 1);
        ft_strlcat(result, "\n", total_len + 1);
        i++;
    }
    return (result);
}

void	ft_free_str_array(char **arr)
{
    int	i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}
