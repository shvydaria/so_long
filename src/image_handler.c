/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-15 11:14:12 by dashvydk          #+#    #+#             */
/*   Updated: 2025-08-15 11:14:12 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_images(t_game *game)
{
	if (game->images)
	{
		if (game->images->wall)
			mlx_delete_image(game->mlx, game->images->wall);
		if (game->images->player)
			mlx_delete_image(game->mlx, game->images->player);
		if (game->images->collectible)
			mlx_delete_image(game->mlx, game->images->collectible);
		if (game->images->exit)
			mlx_delete_image(game->mlx, game->images->exit);
		if (game->images->empty)
			mlx_delete_image(game->mlx, game->images->empty);
		free(game->images);
	}
}

t_images	*init_images(t_game *game)
{
	t_images	*imgs;

	imgs = malloc(sizeof(t_images));
	if (!imgs)
		return (NULL);
	imgs->wall = mlx_texture_to_image(game->mlx, game->textures->wall);
	imgs->player = mlx_texture_to_image(game->mlx, game->textures->player);
	imgs->collectible = mlx_texture_to_image(game->mlx,
			game->textures->collectible);
	imgs->exit = mlx_texture_to_image(game->mlx, game->textures->exit);
	imgs->empty = mlx_texture_to_image(game->mlx, game->textures->empty);
	if (!imgs->wall || !imgs->player || !imgs->collectible || !imgs->exit
		|| !imgs->empty)
	{
		free_images(game);
		return (NULL);
	}
	return (imgs);
}
