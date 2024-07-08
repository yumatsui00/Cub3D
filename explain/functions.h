/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:52:36 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/07 12:21:11 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

#include "all.h"

int		init_data(t_data *data);
int		mainloop(t_data *data);
void	floor_ceiling_casting(t_data *data);
void	wall_casting(t_data *data);
int	key_release(int key, t_data *data);
int	key_press(int key, t_data *data);
int	window_close(t_data *data);

#endif