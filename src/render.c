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

// Simplified collectible initialization
void	init_collectibles(t_game *game)
{
    int y;
    int x;
    int count;
	int instance_id;

    count = 0;
    y = 0;
	// count the collectibles to allocate memory
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            if (game->map[y][x] == 'C')
            {
                // Draw the collectible image
                // mlx_image_to_window(game->mlx, game->images->collectible, 
                //     x * TILE_SIZE, y * TILE_SIZE);
                count++;
            }
            x++;
        }
        y++;
    }
    game->collectibles = count;
	game->collectible_instances = malloc(sizeof(int32_t*) * (count + 1));
	game->collectible_positions = malloc(sizeof(int*) * (count * 2 + 2));
	if (!game->collectible_instances || !game->collectible_positions)
    {
        ft_printf("Error: Failed to allocate memory for collectibles\n");
        // Consider calling cleanup_game and exiting
        return;
    }
	count = 0;
    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
            if (game->map[y][x] == 'C')
            {
                // Draw the collectible and get its instance ID
                instance_id = mlx_image_to_window(game->mlx, game->images->collectible, 
                    x * TILE_SIZE, y * TILE_SIZE);
                
                // Store the instance ID and position
                game->collectible_instances[count] = instance_id;
                game->collectible_positions[count * 2] = x;
                game->collectible_positions[count * 2 + 1] = y;
                count++;
            }
            x++;
        }
        y++;
    }
    ft_printf("Found and rendered %d collectibles\n", game->collectibles);
}

// Renders an individual map tile
void	render_tile(t_game *game, char tile, int x, int y)
{
    // Render the wall tile
    if (tile == '1')
    {
        mlx_image_to_window(game->mlx, game->images->wall, x * TILE_SIZE, y * TILE_SIZE);
    }
    // Render the ground tile for everything else (0, C, P, E)
    else
    {
        mlx_image_to_window(game->mlx, game->images->empty, x * TILE_SIZE, y * TILE_SIZE);
    }

    // Render the exit on top of the ground tile
    if (tile == 'E')
    {
        mlx_image_to_window(game->mlx, game->images->exit, x * TILE_SIZE, y * TILE_SIZE);
    }
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

// void	render_tile(t_game *game, char tile, int x, int y)
// {
// 	// Always render empty (ground) first
// 	if (tile != '1')
// 		mlx_image_to_window(game->mlx, game->images->empty, x * TILE_SIZE, y
// 			* TILE_SIZE);
// 	// Then render the appropriate tile
// 	if (tile == '1')
// 		mlx_image_to_window(game->mlx, game->images->wall, x * TILE_SIZE, y
// 			* TILE_SIZE);
// 	else if (tile == 'P')
// 	{
// 		render_player(game, x, y);
// 		game->map[y][x] = '0'; // Convert P to 0 after finding player position
// 	}
// 	else if (tile == 'C')
// 		mlx_image_to_window(game->mlx, game->images->collectible, x * TILE_SIZE,
// 			y * TILE_SIZE);
// 	else if (tile == 'E')
// 		mlx_image_to_window(game->mlx, game->images->exit, x * TILE_SIZE, y
// 			* TILE_SIZE);
// }

// void	render_map(t_game *game)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	while (game->map[y])
// 	{
// 		x = 0;
// 		while (game->map[y][x])
// 		{
// 			render_tile(game, game->map[y][x], x, y);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// Clear previous frame
// Render new frame
// void	refresh_game(void *param)
// {
// 	t_game		*game;

// 	game = (t_game *)param;
// 	render_map(game);
// 	// Render player at current position
// 	render_player(game, game->player_x, game->player_y);
// }
// 		mlx_image_to_window(game->mlx, game->images->empty, x * TILE_SIZE, y
// 			* TILE_SIZE);
// 	// Then render the appropriate tile
// 	if (tile == '1')
// 		mlx_image_to_window(game->mlx, game->images->wall, x * TILE_SIZE, y
// 			* TILE_SIZE);
// 	else if (tile == 'P')
// 	{
// 		render_player(game, x, y);
// 		game->map[y][x] = '0'; // Convert P to 0 after finding player position
// 	}
// 	else if (tile == 'C')
// 		mlx_image_to_window(game->mlx, game->images->collectible, x * TILE_SIZE,
// 			y * TILE_SIZE);
// 	else if (tile == 'E')
// 		mlx_image_to_window(game->mlx, game->images->exit, x * TILE_SIZE, y
// 			* TILE_SIZE);
// }

// void	render_map(t_game *game)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	while (game->map[y])
// 	{
// 		x = 0;
// 		while (game->map[y][x])
// 		{
// 			render_tile(game, game->map[y][x], x, y);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// Clear previous frame
// Render new frame
// void	refresh_game(void *param)
// {
// 	t_game		*game;

// 	game = (t_game *)param;
// 	render_map(game);
// 	// Render player at current position
// 	render_player(game, game->player_x, game->player_y);
// }
