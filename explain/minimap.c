/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 19:12:44 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/08 13:52:05 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	minimap_casting(t_data *data)
{
	t_mini	mini;

	mini.x = -1;
	while (++mini.x < MINI_W)
	{
		mini.map_x = (int)(data->posX + 6.0 * mini.x / MINI_W - 3.0);
		mini.y = -1;
		while (++mini.y < MINI_H)
		{
			mini.map_y = (int)(data->posY + 6.0 * mini.y / MINI_H - 3.0);
			//!マップによってはここでセグフォしない？
			if (data->map[mini.map_y][mini.map_x] == 0)
				data->buf[mini.y][mini.x] = GREY;
			else
				data->buf[mini.y][mini.x] = BLACK;
		}
	}
	mini.c_y = MINI_H / 2 - 4;
	while (++mini.c_y <= MINI_W / 2 + 3)
	{
		mini.c_x = MINI_W / 2 - 4;
		while (++mini.c_x <= MINI_H / 2 + 3)
			data->buf[mini.c_y][mini.c_x] = GREEN;
	}
}
