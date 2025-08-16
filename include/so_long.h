/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-14 10:59:26 by dashvydk          #+#    #+#             */
/*   Updated: 2025-08-14 10:59:26 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define TILE_SIZE 32     // Base size for all tiles
# define SPRITE_WIDTH 32  // Width of one sprite
# define SPRITE_HEIGHT 32 // Height of one sprite
# define SPRITE_FRAMES 6  // Number of frames per row
# define SPRITE_ROWS 3    // Number of rows in spritesheet
# include "../MLX42/include/MLX42/MLX42.h"
# include "../get_next_line/get_next_line.h"
# include "libft.h"
# include "libftprintf.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_textures
{
	mlx_texture_t	*wall;
	mlx_texture_t	*player;
	mlx_texture_t	*collectible;
	mlx_texture_t	*exit;
	mlx_texture_t	*empty;
}					t_textures;

typedef struct s_images
{
	mlx_image_t		*wall;
	mlx_image_t		*player;
	mlx_image_t		*collectible;
	mlx_image_t		*exit;
	mlx_image_t		*empty;
}					t_images;

typedef struct s_game
{
	char			**map;
	int				player_x;
	int				player_y;
	int				collectibles;
	int				moves;
	mlx_t			*mlx;
	mlx_image_t		*window_image;
	t_textures		*textures;
	t_images		*images;
	int				current_frame;
	mlx_image_t		*current_player_frame;
}					t_game;

// Map utils
char				*read_file_to_str(char *filename);
char				**split_to_2d_array(char *map_str);
int					is_map_rectangular(char **map);

// Map validation
int					check_characters(char **map);
int					check_walls(char **map);
int					count_elements(char **map, char c);
int					validate_map(char **map);

// Texture management
t_textures			*load_textures(void);
void				free_textures(t_textures *textures);

// Image handling
t_images			*init_images(t_game *game);
void				free_images(t_game *game);

// Rendering
void				render_map(t_game *game);
void				render_tile(t_game *game, char tile, int x, int y);
void				render_player(t_game *game, int px, int py);
void				refresh_game(void *param);

// Player management
void				handle_keypress(mlx_key_data_t keydata, void *param);
void				init_player(t_game *game);

#endif
