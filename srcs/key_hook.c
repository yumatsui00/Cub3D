/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:35:07 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/19 01:40:34 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

int	key_press(int key, t_data *data)
{
	if (key == ESC)
		window_close(data);
	else if (key == W)
		data->key_w = GO;
	else if (key == A)
		data->key_a = GO;
	else if (key == S)
		data->key_s = GO;
	else if (key == D)
		data->key_d = GO;
	else if (key == SP)
		data->dash = DASH;
	else if (key == LEFT)
		data->key_left = GO;
	else if (key == RIGHT)
		data->key_right = GO;
	else if (key == M)
		data->mini = !(data->mini);
	else if (key == TAB)
		data->mouse = !(data->mouse);
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == W)
		data->key_w = STOP;
	else if (key == A)
		data->key_a = STOP;
	else if (key == S)
		data->key_s = STOP;
	else if (key == D)
		data->key_d = STOP;
	else if (key == SP)
		data->dash = 1;
	else if (key == LEFT)
		data->key_left = STOP;
	else if (key == RIGHT)
		data->key_right = STOP;
	return (0);
}
