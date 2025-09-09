/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:32:11 by dashvydk          #+#    #+#             */
/*   Updated: 2025/08/27 15:45:30 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	init_mlx(t_game *game)
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

static void	init_window(t_game *game)
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

int	init_game_data(t_game *game, char *map_file)
{
	char	*map_str;

	ft_memset(game, 0, sizeof(t_game));
	map_str = read_file_to_str(map_file);
	if (!map_str)
		return (ft_printf("Error\nFailed to read map file\n"), 0);
	game->map = split_to_2d_array(map_str);
	free(map_str);
	if (!game->map || !validate_map(game->map))
		return (cleanup_game(game), 0);
	if (!is_path_valid(game))
		return (cleanup_game(game), 0);
	return (1);
}

int	setup_graphics_and_objects(t_game *game)
{
	init_mlx(game);
	init_window(game);
	game->textures = load_textures();
	if (!game->textures)
		return (cleanup_game(game), 0);
	game->images = init_images(game);
	if (!game->images)
	{
		cleanup_game(game);
		ft_printf("Error\nFailed to create images from textures\n");
		return (0);
	}
	render_map(game);
	init_collectibles(game);
	init_player(game);
	return (1);
}
