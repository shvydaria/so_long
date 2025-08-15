/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-14 10:59:26 by dashvydk          #+#    #+#             */
/*   Updated: 2025-08-14 10:59:26 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../get_next_line/get_next_line.h"
# include "libft.h"
# include "libftprintf.h"

// Map utils
char	*read_file_to_str(char *filename);
char	**split_to_2d_array(char *map_str);
int		is_map_rectangular(char **map);

// Map validation
int		check_characters(char **map);
int		check_walls(char **map);
int		count_elements(char **map, char c);
int		validate_map(char **map);

typedef struct s_game
{
    char    **map;          // 2D map array
    int     player_x;       // Player's X position
    int     player_y;       // Player's Y position
    int     collectibles;   // Number of collectibles remaining
    int     moves;          // Number of moves made
    mlx_t   *mlx;          // MLX instance
	mlx_image_t *window_image;
}   t_game;

#endif
