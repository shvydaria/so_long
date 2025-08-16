/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-15 13:11:57 by dashvydk          #+#    #+#             */
/*   Updated: 2025-08-15 13:11:57 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	bool	moved;
	int		new_x;
	int		new_y;

	game = (t_game *)param;
	moved = false;
	if (keydata.action != MLX_PRESS)
		return ;
	// Store current position
	new_x = game->player_x;
	new_y = game->player_y;
	// which key was pressed and update position
	if (keydata.key == MLX_KEY_W)
		new_y--;
	else if (keydata.key == MLX_KEY_S)
		new_y++;
	else if (keydata.key == MLX_KEY_A)
		new_x--;
	else if (keydata.key == MLX_KEY_D)
		new_x++;
	else
		return ;
	// collisions with walls
	if (game->map[new_y][new_x] != '1')
	{
		// Update player position
		game->player_x = new_x;
		game->player_y = new_y;
		game->moves++;
		ft_printf("Moves: %d\n", game->moves);
		moved = true;
	}
	// Handle collectibles
	if (game->map[new_y][new_x] == 'C')
	{
		game->collectibles--;
		game->map[new_y][new_x] = '0';
	}
}

void	init_player(t_game *game)
{
	int	y;
	int	x;

	// Find player starting position
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}
