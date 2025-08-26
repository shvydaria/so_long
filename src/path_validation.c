/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshvydka <dshvydka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:10:33 by dshvydka          #+#    #+#             */
/*   Updated: 2025/08/26 19:10:49 by dshvydka         ###   ########.fr       */
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
                return;
            (*x)++;
        }
        (*y)++;
    }
}

// The recursive flood-fill algorithm
static void flood_fill(char **map_copy, int x, int y, int width, int height)
{
    // Base cases: stop if out of bounds, on a wall, or already visited.
    if (y < 0 || y >= height || x < 0 || x >= width || 
        map_copy[y][x] == '1' || map_copy[y][x] == 'F')
    {
        return;
    }

    // Mark the current tile as 'F' for "Filled"
    map_copy[y][x] = 'F';

    // Recursively call for all four directions
    flood_fill(map_copy, x + 1, y, width, height);
    flood_fill(map_copy, x - 1, y, width, height);
    flood_fill(map_copy, x, y + 1, width, height);
    flood_fill(map_copy, x, y - 1, width, height);
}

// Main function to check if the path is valid
int	is_path_valid(t_game *game)
{
    char	**map_copy;
    int		x;
    int		y;
    int		height;

    map_copy = split_to_2d_array(ft_strarr_join(game->map));
    if (!map_copy)
        return (0);

    height = 0;
    while(game->map[height])
        height++;

    find_start_pos(map_copy, &x, &y);
    flood_fill(map_copy, x, y, ft_strlen(map_copy[0]), height);

    y = 0;
    while (map_copy[y])
    {
        x = 0;
        while (map_copy[y][x])
        {
            // If we find a collectible or exit that wasn't filled, path is invalid
            if (map_copy[y][x] == 'C' || map_copy[y][x] == 'E')
            {
                ft_printf("Error\nMap has an invalid path. Unreachable item or exit.\n");
                ft_free_str_array(map_copy);
                return (0);
            }
            x++;
        }
        y++;
    }
    ft_free_str_array(map_copy);
    return (1);
}
