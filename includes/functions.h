/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:52:36 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/09 14:39:43 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "all.h"

int			init_data(t_data *data);
int			mainloop(t_data *data);
void		floor_ceiling_casting(t_data *data);
void		wall_casting(t_data *data);
int			key_release(int key, t_data *data);
int			key_press(int key, t_data *data);
int			window_close(t_data *data);
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