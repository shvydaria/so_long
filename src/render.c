/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-15 11:21:51 by dashvydk          #+#    #+#             */
/*   Updated: 2025-08-15 11:21:51 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	render_player(t_game *game, int px, int py)
{
	mlx_texture_t	*player_tex;
	mlx_image_t		*player_frame;
	uint32_t		frame_x;
	uint32_t		frame_y;
	uint32_t		pos;
	uint32_t		y;
	uint32_t		x;

	player_tex = game->textures->player;
	if (game->current_player_frame)
		mlx_delete_image(game->mlx, game->current_player_frame);
	frame_x = (game->current_frame % SPRITE_FRAMES) * SPRITE_WIDTH;
	frame_y = ((game->current_frame / SPRITE_FRAMES) % SPRITE_ROWS)
		* SPRITE_HEIGHT;
	// create a temporary image with the full texture
	player_frame = mlx_texture_to_image(game->mlx, player_tex);
	if (!player_frame)
		return ;
	// crop the image by making all pixels outside our frame transparent
	y = 0;
	while (y < player_tex->height)
	{
		x = 0;
		while (x < player_tex->width)
		{
			if (x < frame_x || x >= frame_x + SPRITE_WIDTH || y < frame_y
				|| y >= frame_y + SPRITE_HEIGHT)
			{
				pos = (y * player_tex->width + x) * 4;
				player_frame->pixels[pos + 3] = 0; // Set alpha to 0
			}
			x++;
		}
		y++;
	}
	if (mlx_image_to_window(game->mlx, player_frame, px * TILE_SIZE, py
			* TILE_SIZE) >= 0)
		game->current_player_frame = player_frame;
	else
		mlx_delete_image(game->mlx, player_frame);
}

void	render_tile(t_game *game, char tile, int x, int y)
{
	// Always render empty (ground) first
	if (tile != '1')
		mlx_image_to_window(game->mlx, game->images->empty, x * TILE_SIZE, y
			* TILE_SIZE);
	// Then render the appropriate tile
	if (tile == '1')
		mlx_image_to_window(game->mlx, game->images->wall, x * TILE_SIZE, y
			* TILE_SIZE);
	else if (tile == 'P')
	{
		render_player(game, x, y);
		game->map[y][x] = '0'; // Convert P to 0 after finding player position
	}
	else if (tile == 'C')
		mlx_image_to_window(game->mlx, game->images->collectible, x * TILE_SIZE,
			y * TILE_SIZE);
	else if (tile == 'E')
		mlx_image_to_window(game->mlx, game->images->exit, x * TILE_SIZE, y
			* TILE_SIZE);
}

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

// Clear previous frame
// Render new frame
// Update animation frame
void	refresh_game(void *param)
{
	t_game		*game;
	static int	frame_count = 0;

	game = (t_game *)param;
	render_map(game);
	// Render player at current position
	render_player(game, game->player_x, game->player_y);
	frame_count++;
	if (frame_count >= 10)
	{
		game->current_frame++;
		if (game->current_frame >= SPRITE_FRAMES)
			game->current_frame = 0;
		frame_count = 0;
	}
}
