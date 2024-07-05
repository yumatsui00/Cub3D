/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:35:07 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/05 19:46:31 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	key_press(int key, t_data *data)
{
	if (key == ESC)
	{
		window_close(data);
		exit(0);
	}
	else if (key == W)
		data->key_w = GO;
	else if (key == A)
		data->key_a = GO;
	else if (key == S)
		data->key_s = GO;
	else if (key == D)
		data->key_d = GO;
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
	return (0);
}
