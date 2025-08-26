/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-15 13:11:57 by dashvydk          #+#    #+#             */
/*   Updated: 2025-08-15 13:11:57 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_player(t_game *game)
{
    int	y;
    int	x;

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
                game->player_image = mlx_texture_to_image(game->mlx, game->textures->player);
                if (!game->player_image)
                {
                    ft_printf("Failed to create player image from texture!\n");
                    return;
                }
                if (mlx_image_to_window(game->mlx, game->player_image,
                    x * TILE_SIZE, y * TILE_SIZE) < 0)
                {
                    ft_printf("Failed to draw player to window!\n");
                    return;
                }
                ft_printf("Player created at (%d,%d)\n", x, y);
                // Mark the player's starting position as empty
                game->map[y][x] = '0';
                return;
            }
            x++;
        }
        y++;
    }
}

void	update_moves(t_game *game)
{
    game->moves++;
    ft_printf("Moves: %d\n", game->moves);
}

// Move player up if not blocked by a wall
void	move_up(t_game *game)
{
	 int y_pos = game->player_y;
    int x_pos = game->player_x;
    
    // Check for wall OR exit with remaining collectibles
    if (game->map[y_pos - 1][x_pos] == MAP_WALL ||
        (game->map[y_pos - 1][x_pos] == 'E' && game->collectibles > 0))
        return;

    game->player_image->instances[0].y -= MOVE;
    game->player_y = y_pos - 1;
    update_moves(game);
    check_player_position(game);
}

// Move player right if not blocked by a wall
void	move_right(t_game *game)
{
	int y_pos = game->player_y;
    int x_pos = game->player_x;
	
	 if (game->map[y_pos][x_pos + 1] == MAP_WALL ||
        (game->map[y_pos][x_pos + 1] == 'E' && game->collectibles > 0))
        return;

    game->player_image->instances[0].x += MOVE;
    game->player_x = x_pos + 1;
    update_moves(game);
    check_player_position(game);
}

void	move_down(t_game *game)
{
    int y_pos = game->player_y;
    int x_pos = game->player_x;
    
    if (game->map[y_pos + 1][x_pos] == MAP_WALL ||
       (game->map[y_pos + 1][x_pos] == 'E' && game->collectibles > 0))
        return;
    
        game->player_image->instances[0].y += MOVE;
        game->player_y = y_pos + 1;
        update_moves(game);
        check_player_position(game); // Add this call
}
void	move_left(t_game *game)
{
    int y_pos = game->player_y;
    int x_pos = game->player_x;

    if (game->map[y_pos][x_pos - 1] == MAP_WALL ||
       (game->map[y_pos][x_pos - 1] == 'E' && game->collectibles > 0))
        return;

    game->player_image->instances[0].x -= MOVE;
    game->player_x = x_pos - 1;
    update_moves(game);
    check_player_position(game); // Add this call
}

// Check for collectibles at player's position and collect them
void	collect_collectibles(t_game *game)
{
	int y_pos = game->player_image->instances[0].y / TILE_SIZE;
	int x_pos = game->player_image->instances[0].x / TILE_SIZE;
	int i;
	
	if (game->map[y_pos][x_pos] == 'C')
	{
		// Mark as collected in the map
		game->map[y_pos][x_pos] = '0';
		game->collectibles--;
		
		// Find and hide the collectible instance at this position
		i = 0;
		while (i < game->collectibles + 1)
		{
			if (game->collectible_positions[i*2] == x_pos && 
				game->collectible_positions[i*2+1] == y_pos)
			{
				// Hide the collectible by disabling its instance
				int instance_id = game->collectible_instances[i];
				game->images->collectible->instances[instance_id].enabled = false;
				
				ft_printf("Collected item at (%d,%d)! Remaining: %d\n", 
					x_pos, y_pos, game->collectibles);				
				break;
			}
			i++;
		}
	}
}

void	check_player_position(t_game *game)
{
    int y_pos = game->player_y;
    int x_pos = game->player_x;
    size_t i;

    // Check for collecting an item
    if (game->map[y_pos][x_pos] == 'C')
    {
        game->map[y_pos][x_pos] = '0';
        game->collectibles--;
        ft_printf("Item collected! Remaining: %d\n", game->collectibles);

        // Find the instance of the collected item and disable it
        i = 0;
        while (i < game->images->collectible->count)
        {
            if (game->images->collectible->instances[i].x == x_pos * TILE_SIZE &&
                game->images->collectible->instances[i].y == y_pos * TILE_SIZE)
            {
                game->images->collectible->instances[i].enabled = false;
                break;
            }
            i++;
        }
    }
    // Check for exiting the map
    if (game->map[y_pos][x_pos] == 'E')
    {
        if (game->collectibles == 0)
        {
            ft_printf("You win! Total moves: %d\n", game->moves);
            mlx_close_window(game->mlx);
        }
        else
        {
            ft_printf("You must collect all %d items before exiting!\n", game->collectibles);
        }
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
		mlx_close_window(game->mlx);	// Check for collectibles after movement
	// collect_collectibles(game);
}



