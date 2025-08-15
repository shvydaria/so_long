/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dashvydk <dashvydk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-24 12:23:55 by dashvydk          #+#    #+#             */
/*   Updated: 2025-04-24 12:23:55 by dashvydk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*append_buffer(char *basin_buffer, char *read_buffer);
char	*read_from_file(char *buffer, int fd);
char	*extract_line(char *buffer);
char	*update_buff(char *buffer);
// utility functions
char	*ft_strchr(const char *str, int chr);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_calloc(size_t num, size_t size);
void	ft_bzero(void *s, size_t n);

#endif
