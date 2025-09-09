/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 11:14:12 by dashvydk          #+#    #+#             */
/*   Updated: 2025/08/28 14:54:01 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Initialize the images that will be used in the game
// Convert all textures to images
t_images	*init_images(t_game *game)
{
	t_images	*images;

	images = malloc(sizeof(t_images));
	if (!images)
		return (NULL);
	images->wall = mlx_texture_to_image(game->mlx, game->textures->wall);
	images->player = mlx_texture_to_image(game->mlx, game->textures->player);
	images->collectible = mlx_texture_to_image(game->mlx,
			game->textures->collectible);
	images->exit = mlx_texture_to_image(game->mlx, game->textures->exit);
	images->empty = mlx_texture_to_image(game->mlx, game->textures->empty);
	if (!images->wall || !images->player || !images->collectible
		|| !images->exit || !images->empty)
	{
		free_images(game->mlx, images);
		return (NULL);
	}
	return (images);
}

// Free all images from game
void	free_images(mlx_t *mlx, t_images *images)
{
	if (images)
	{
		if (images->wall)
			mlx_delete_image(mlx, images->wall);
		if (images->player)
			mlx_delete_image(mlx, images->player);
		if (images->collectible)
			mlx_delete_image(mlx, images->collectible);
		if (images->exit)
			mlx_delete_image(mlx, images->exit);
		if (images->empty)
			mlx_delete_image(mlx, images->empty);
		free(images);
	}
}
