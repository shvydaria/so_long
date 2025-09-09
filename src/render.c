/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:21:51 by dashvydk          #+#    #+#             */
/*   Updated: 2025/08/27 16:04:41 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	render_tile(t_game *game, char tile, int x, int y)
{
	if (tile == '1')
		mlx_image_to_window(game->mlx, game->images->wall, x * TILE_SIZE, y
			* TILE_SIZE);
	else
		mlx_image_to_window(game->mlx, game->images->empty, x * TILE_SIZE, y
			* TILE_SIZE);
	if (tile == 'E')
		mlx_image_to_window(game->mlx, game->images->exit, x * TILE_SIZE, y
			* TILE_SIZE);
}

// Renders the entire map
void	render_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			render_tile(game, game->map[y][x], x, y);
			x++;
		}
		y++;
	}
}
