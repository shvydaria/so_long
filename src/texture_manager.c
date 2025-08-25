/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-14 12:30:01 by dashvydk          #+#    #+#             */
/*   Updated: 2025-08-14 12:30:01 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_textures(t_textures *textures)
{
	if (textures->wall)
		mlx_delete_texture(textures->wall);
	if (textures->player)
		mlx_delete_texture(textures->player);
	if (textures->collectible)
		mlx_delete_texture(textures->collectible);
	if (textures->exit)
		mlx_delete_texture(textures->exit);
	if (textures->empty)
		mlx_delete_texture(textures->empty);
	free(textures);
}

void	debug_texture(mlx_texture_t *texture)
{
	ft_printf("Texture dimensions: %dx%d\n", texture->width, texture->height);
}

// creates a pointer to store structure
// allocates memory for the structure
// creates a container (structure) to hold all textures in one organized package
t_textures	*load_textures(void)
{
	t_textures	*textures;

	textures = malloc(sizeof(t_textures));
	if (!textures)
		return (NULL);
	textures->wall = mlx_load_png("./assets/wall.png");
	textures->player = mlx_load_png("./assets/ducky_spritesheet.png");
	debug_texture(textures->player);
	textures->collectible = mlx_load_png("./assets/collectible.png");
	textures->exit = mlx_load_png("./assets/exit.png");
	textures->empty = mlx_load_png("./assets/ground.png");
	if (!textures->wall || !textures->player || !textures->collectible
		|| !textures->exit || !textures->empty)
	{
		free_textures(textures);
		return (NULL);
	}
	return (textures);
}
