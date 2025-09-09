/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:10:33 by dshvydka          #+#    #+#             */
/*   Updated: 2025/08/28 14:36:39 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// A helper function to find the starting coordinates of a character
static void	find_start_pos(char **map, int *x, int *y)
{
	*y = 0;
	while (map[*y])
	{
		*x = 0;
		while (map[*y][*x])
		{
			if (map[*y][*x] == 'P')
				return ;
			(*x)++;
		}
		(*y)++;
	}
}

// The recursive flood-fill algorithm
// 'F' for "Filled"
static void	flood_fill(char **map_copy, t_point pos, t_point size)
{
	if (pos.y < 0 || pos.y >= size.y || pos.x < 0 || pos.x >= size.x
		|| map_copy[pos.y][pos.x] == '1' || map_copy[pos.y][pos.x] == 'F')
	{
		return ;
	}
	map_copy[pos.y][pos.x] = 'F';
	flood_fill(map_copy, (t_point){pos.x + 1, pos.y}, size);
	flood_fill(map_copy, (t_point){pos.x - 1, pos.y}, size);
	flood_fill(map_copy, (t_point){pos.x, pos.y + 1}, size);
	flood_fill(map_copy, (t_point){pos.x, pos.y - 1}, size);
}

static int	check_items_reachable(char **map_copy)
{
	int	x;
	int	y;

	y = 0;
	while (map_copy[y])
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == 'C' || map_copy[y][x] == 'E')
			{
				ft_printf("Error\nMap has an invalid path."
					"Unreachable item or exit.\n");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

// Main function to check if the path is valid
int	is_path_valid(t_game *game)
{
	char	**map_copy;
	char	*map_str;
	t_point	size;
	t_point	start;
	int		is_valid;

	map_str = ft_strarr_join(game->map);
	if (!map_str)
		return (0);
	map_copy = split_to_2d_array(map_str);
	free(map_str);
	if (!map_copy)
		return (0);
	size.y = 0;
	while (game->map[size.y])
		size.y++;
	size.x = ft_strlen(map_copy[0]);
	find_start_pos(map_copy, &start.x, &start.y);
	flood_fill(map_copy, start, size);
	is_valid = check_items_reachable(map_copy);
	ft_free_str_array(map_copy);
	return (is_valid);
}
