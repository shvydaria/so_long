/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:05:30 by dashvydk          #+#    #+#             */
/*   Updated: 2025/08/28 14:36:14 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Handles cleanup
void	cleanup_game(t_game *game)
{
	int	i;

	if (game->textures)
		free_textures(game->textures);
	if (game->images)
		free_images(game->mlx, game->images);
	if (game->collectible_instances)
		free(game->collectible_instances);
	if (game->collectible_positions)
		free(game->collectible_instances);
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
	if (game->player_image)
		mlx_delete_image(game->mlx, game->player_image);
	if (game->mlx)
		mlx_terminate(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		len;

	if (argc != 2)
		return (ft_printf("Error\nUsage: ./so_long <map.ber>\n"), 1);
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".ber", 4) != 0)
		return (ft_printf("Error\nMap file must have a .ber extension\n"), 1);
	if (!init_game_data(&game, argv[1]))
		return (1);
	if (!setup_graphics_and_objects(&game))
		return (1);
	mlx_key_hook(game.mlx, &my_key_hook, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
