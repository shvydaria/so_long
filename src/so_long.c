/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          #+#    #+#             */
/*   Created: 2025-08-14 11:30:22 by dashvydk          #+#    #+#             */
/*   Updated: 2025-08-14 11:30:22 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Handles cleanup
void	cleanup_game(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = 0;
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
	if (game->current_player_frame)
		mlx_delete_image(game->mlx, game->current_player_frame);
	if (game->mlx)
		mlx_terminate(game->mlx);
}

void	init_mlx(t_game *game)
{
	int	width;
	int	height;

	height = 0;
	while (game->map[height])
		height++;
	width = ft_strlen(game->map[0]);
	game->mlx = mlx_init(width * 32, height * 32, "so_long", true);
	if (!game->mlx)
	{
		ft_printf("Error\nFailed to initialize MLX42\n");
		cleanup_game(game);
		exit(1);
	}
}

// Create window image
// Display the image
void	init_window(t_game *game)
{
	mlx_image_t	*window_image;

	window_image = mlx_new_image(game->mlx, game->mlx->width,
			game->mlx->height);
	if (!window_image)
	{
		ft_printf("Error\nFailed to create window image\n");
		cleanup_game(game);
		exit(1);
	}
	if (mlx_image_to_window(game->mlx, window_image, 0, 0) < 0)
	{
		ft_printf("Error\nFailed to put image to window\n");
		mlx_delete_image(game->mlx, window_image);
		cleanup_game(game);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_game	game;
	char	*map_str;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./so_long <map.ber>\n");
		return (1);
	}
	// Initialize game struct
	ft_memset(&game, 0, sizeof(t_game));
	// Read and validate map
	map_str = read_file_to_str(argv[1]);
	if (!map_str)
	{
		ft_printf("Error\nFailed to read map file\n");
		return (1);
	}
	game.map = split_to_2d_array(map_str);
	free(map_str);
	if (!game.map || !validate_map(game.map))
	{
		cleanup_game(&game);
		return (1);
	}
	// Initialize MLX and window
	init_mlx(&game);
	init_window(&game);
	// Load textures and images
	game.textures = load_textures();
	if (!game.textures)
	{
		cleanup_game(&game);
		return (1);
	}
	game.images = init_images(&game);
	if (!game.images)
	{
		cleanup_game(&game);
		return (1);
	}
	// After loading textures and images...
	init_player(&game);
	// Set up all hooks
	mlx_key_hook(game.mlx, &handle_keypress, &game);
	mlx_loop_hook(game.mlx, &refresh_game, &game);
	// Initial render
	render_map(&game);
	// Start game loop
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
