/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:18:31 by dashvydk          #+#    #+#             */
/*   Updated: 2025/08/27 13:19:28 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	update_moves(t_game *game)
{
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

// Move player up if not blocked by a wall
void	move_up(t_game *game)
{
	int	y_pos;
	int	x_pos;

	y_pos = game->player_y;
	x_pos = game->player_x;
	if (game->map[y_pos - 1][x_pos] == MAP_WALL || (game->map[y_pos
			- 1][x_pos] == 'E' && game->collectibles > 0))
		return ;
	game->player_image->instances[0].y -= MOVE;
	game->player_y = y_pos - 1;
	update_moves(game);
	check_player_position(game);
}

// Move player right if not blocked by a wall
void	move_right(t_game *game)
{
	int	y_pos;
	int	x_pos;

	y_pos = game->player_y;
	x_pos = game->player_x;
	if (game->map[y_pos][x_pos + 1] == MAP_WALL || (game->map[y_pos][x_pos
			+ 1] == 'E' && game->collectibles > 0))
		return ;
	game->player_image->instances[0].x += MOVE;
	game->player_x = x_pos + 1;
	update_moves(game);
	check_player_position(game);
}

void	move_down(t_game *game)
{
	int	y_pos;
	int	x_pos;

	y_pos = game->player_y;
	x_pos = game->player_x;
	if (game->map[y_pos + 1][x_pos] == MAP_WALL || (game->map[y_pos
			+ 1][x_pos] == 'E' && game->collectibles > 0))
		return ;
	game->player_image->instances[0].y += MOVE;
	game->player_y = y_pos + 1;
	update_moves(game);
	check_player_position(game);
}

void	move_left(t_game *game)
{
	int	y_pos;
	int	x_pos;

	y_pos = game->player_y;
	x_pos = game->player_x;
	if (game->map[y_pos][x_pos - 1] == MAP_WALL || (game->map[y_pos][x_pos
			- 1] == 'E' && game->collectibles > 0))
		return ;
	game->player_image->instances[0].x -= MOVE;
	game->player_x = x_pos - 1;
	update_moves(game);
	check_player_position(game);
}
