/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 19:12:44 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/09 15:27:22 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

void	minimap_casting(t_data *data)
{
	t_mini	mini;

	mini.x = -1;
	//update thr buf only in the size of minimap
	while (++mini.x < MINI_W)
	{
		//Minimap showd 36 blocks in total. 6 * 6 map.
		//which means you better devide the minimap into 6 * 6!
		mini.map_x = (int)(data->pos_x + 6.0 * mini.x / MINI_W - 3.0);
		mini.y = -1;
		while (++mini.y < MINI_H)
		{
			mini.map_y = (int)(data->pos_y + 6.0 * mini.y / MINI_H - 3.0);
			//where you can travel is painted grey. othres are black
			if (data->map[mini.map_y][mini.map_x] == 0)
				data->buf[mini.y][mini.x] = GREY;
			else
				data->buf[mini.y][mini.x] = BLACK;
		}
	}
	//add yourself in the center of minimap. only 36 pixels!
	mini.c_y = MINI_H / 2 - 4;
	while (++mini.c_y <= MINI_W / 2 + 3)
	{
		mini.c_x = MINI_W / 2 - 4;
		while (++mini.c_x <= MINI_H / 2 + 3)
			data->buf[mini.c_y][mini.c_x] = GREEN;
	}
}
