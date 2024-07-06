/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:52:47 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/06 16:30:14 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include "data.h"
# include "functions.h"
# include "key.h"
# include "raycast.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define OK 1
# define ERROR 0
# define MALLOCERROR -1
# include "libft/libft.h"

struct		s_rgb
{
	int		r;
	int		g;
	int		b;
} typedef t_rgb;

struct		s_position
{
	int		x;
	int		y;
	int		direction;
} typedef t_position;

struct		s_analyze
{
	char	*n_texture_path;
	char	*s_texture_path;
	char	*e_texture_path;
	char	*w_texture_path;
	char	*f_texture_path;
	char	*c_texture_path;
	int		direction;
	t_rgb	f_rgb;
	t_rgb	c_rgb;
	int		**map;
} typedef t_analyze;

# define NORTH 4
# define SOUTH 5
# define WEST 6
# define EAST 7

t_data		analyze_cub(char *filepath);
char		*get_next_line(int fd);
void		assignment_texture(t_analyze *data, char *line);
void		assignment_rgb(t_analyze *data, char *line);
t_position	assignment_all(t_analyze *data, char *filepath);
t_position	analyze_map(int **map);
void		assignment_map(t_analyze *data, char **map);

int			*make_off_line(int width, int num);
int			get_max_width_intpp(int **map);
int			get_max_width_charpp(char **map);
int			get_now_width(int **map, int height);
int			get_now_height(int **map, int width);

char		*get_next_line(int fd);
int			ft_intplen(int *line);
char		**ft_strppjoin(char **map, char *row);
int			**ft_intppjoin(int **map, int *row);
int			ft_strpplen(char **map);
int			ft_intpplen(int **map);

void		free_double_ptr(char **s);
void		free_double_ptr_int(int **s);
void		debug_map(char **map);
void		debug_intline(int *line);
void		debug_intmap(int **map);
#endif