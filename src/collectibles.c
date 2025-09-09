/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectibles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:00:54 by dashvydk          #+#    #+#             */
/*   Updated: 2025/08/27 15:00:56 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	count_collectibles(t_game *game)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'C')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	place_collectibles(t_game *game)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'C')
			{
				mlx_image_to_window(game->mlx, game->images->collectible, x
					* TILE_SIZE, y * TILE_SIZE);
				count++;
			}
			x++;
		}
		y++;
	}
}

// Simplified collectible initialization
void	init_collectibles(t_game *game)
{
	game->collectibles = count_collectibles(game);
	game->images->collectible = mlx_texture_to_image(game->mlx,
			game->textures->collectible);
	if (!game->images->collectible)
		return ;
	place_collectibles(game);
}
