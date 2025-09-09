/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 13:11:57 by dashvydk          #+#    #+#             */
/*   Updated: 2025/08/27 15:45:12 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	find_player_start(t_game *game, int *x, int *y)
{
	*y = 0;
	while (game->map[*y])
	{
		*x = 0;
		while (game->map[*y][*x])
		{
			if (game->map[*y][*x] == 'P')
				return ;
			(*x)++;
		}
		(*y)++;
	}
}

void	init_player(t_game *game)
{
	int	x;
	int	y;

	find_player_start(game, &x, &y);
	game->player_x = x;
	game->player_y = y;
	game->player_image = mlx_texture_to_image(game->mlx,
			game->textures->player);
	if (!game->player_image)
		return ;
	if (mlx_image_to_window(game->mlx, game->player_image, x * TILE_SIZE, y
			* TILE_SIZE) < 0)
		return ;
	game->map[y][x] = '0';
}

static void	handle_collectible(t_game *game, int x_pos, int y_pos)
{
	size_t	i;

	game->map[y_pos][x_pos] = '0';
	game->collectibles--;
	i = 0;
	while (i < game->images->collectible->count)
	{
		if (game->images->collectible->instances[i].x == x_pos * TILE_SIZE
			&& game->images->collectible->instances[i].y == y_pos * TILE_SIZE)
		{
			game->images->collectible->instances[i].enabled = false;
			break ;
		}
		i++;
	}
}

void	check_player_position(t_game *game)
{
	int	y_pos;
	int	x_pos;

	y_pos = game->player_y;
	x_pos = game->player_x;
	if (game->map[y_pos][x_pos] == 'C')
		handle_collectible(game, x_pos, y_pos);
	if (game->map[y_pos][x_pos] == 'E')
	{
		if (game->collectibles == 0)
			mlx_close_window(game->mlx);
	}
}

// Key hook function to handle keyboard input
void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if ((keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		|| (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE))
		move_up(game);
	else if ((keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		|| (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE))
		move_right(game);
	else if ((keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		|| (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE))
		move_down(game);
	else if ((keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		|| (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE))
		move_left(game);
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(game->mlx);
}
