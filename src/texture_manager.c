/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:30:01 by dashvydk          #+#    #+#             */
/*   Updated: 2025/08/27 16:23:38 by dashvydk         ###   ########.fr       */
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

static int	load_png_texture(mlx_texture_t **texture, const char *path)
{
	*texture = mlx_load_png(path);
	if (!*texture)
	{
		ft_printf("Error\nFailed to load texture: %s\n", path);
		return (0);
	}
	return (1);
}

t_textures	*load_textures(void)
{
	t_textures	*textures;
	int			success;

	textures = ft_calloc(1, sizeof(t_textures));
	if (!textures)
		return (NULL);
	success = 1;
	if (!load_png_texture(&textures->wall, "./assets/wall.png"))
		success = 0;
	if (!load_png_texture(&textures->player, "./assets/ducky.png"))
		success = 0;
	if (!load_png_texture(&textures->collectible, "./assets/collectible.png"))
		success = 0;
	if (!load_png_texture(&textures->exit, "./assets/exit.png"))
		success = 0;
	if (!load_png_texture(&textures->empty, "./assets/ground.png"))
		success = 0;
	if (!success)
	{
		free_textures(textures);
		return (NULL);
	}
	return (textures);
}
