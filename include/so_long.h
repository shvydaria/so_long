/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshvydka <dshvydka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 10:59:26 by dashvydk          #+#    #+#             */
/*   Updated: 2025/08/26 19:15:59 by dshvydka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define TILE_SIZE 32      // Base size for all tiles
# define MOVE 32          // Movement distance
# define MAP_WALL '1'     // Wall character in map

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

typedef struct s_collectible
{
	mlx_image_t		*image;
	int				x;
	int				y;
	int				collected;
}					t_collectible;

typedef struct s_game
{
	char			**map;
	int				player_x;
	int				player_y;
	int				collectibles;
	int				moves;
	mlx_t			*mlx;
	t_textures		*textures;
	t_images		*images;
	mlx_image_t		*player_image;  // Player image instance
	int32_t			*collectible_instances; // Array of collectible instance IDs
	int				*collectible_positions; // Array of collectible positions [x1,y1,x2,y2,...]
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
int					is_path_valid(t_game *game);
void				ft_free_str_array(char **arr);
char				*ft_strarr_join(char **arr);

// Texture management
t_textures			*load_textures(void);
void				free_textures(t_textures *textures);

// Image handling
t_images			*init_images(t_game *game);
void				free_images(t_game *game);

// Rendering
void				render_map(t_game *game);
void				render_tile(t_game *game, char tile, int x, int y);
void				init_collectibles(t_game *game);

// Player management
void				init_player(t_game *game);
void				update_moves(t_game *game);
void				move_up(t_game *game);
void				move_right(t_game *game);
void				move_down(t_game *game);
void				move_left(t_game *game);
void				my_key_hook(mlx_key_data_t keydata, void *param);
void				collect_collectibles(t_game *game);
void				check_player_position(t_game *game);

// Game management
void				cleanup_game(t_game *game);

#endif

