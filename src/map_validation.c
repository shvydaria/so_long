/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-14 12:30:01 by dashvydk          #+#    #+#             */
/*   Updated: 2025-08-14 12:30:01 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Makes sure your map only contains valid characters ('0', '1', 'C', 'E', 'P')
// Without this, you might try to render invalid characters later
int	check_characters(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'C'
				&& map[i][j] != 'E' && map[i][j] != 'P')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

// Ensures the map is surrounded by walls ('1')
// Without this, your player could walk off the map!
int	check_walls(char **map)
{
	int	i;
	int	j;
	int	height;
	int	width;

	height = 0;
	while (map[height])
		height++;
	width = ft_strlen(map[0]);
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if ((i == 0 || i == height - 1 || j == 0 || j == width - 1)
				&& map[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
// Makes sure you have:
// Exactly 1 player (P)
// Exactly 1 exit (E)
// At least 1 collectible (C)
// Without this, your game wouldn't be playable

int	count_elements(char **map, char c)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}
// Runs all these checks and prints appropriate error messages

int	validate_map(char **map)
{
	if (!is_map_rectangular(map))
		return (ft_printf("Error\nMap is not rectangular\n"), 0);
	if (!check_characters(map))
		return (ft_printf("Error\nInvalid characters in map\n"), 0);
	if (!check_walls(map))
		return (ft_printf("Error\nMap is not surrounded by walls\n"), 0);
	if (count_elements(map, 'P') != 1)
		return (ft_printf("Error\nInvalid number of starting positions\n"), 0);
	if (count_elements(map, 'E') != 1)
		return (ft_printf("Error\nInvalid number of exits\n"), 0);
	if (count_elements(map, 'C') < 1)
		return (ft_printf("Error\nNo collectibles found\n"), 0);
	return (1);
}
