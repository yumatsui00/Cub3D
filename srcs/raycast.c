/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:20:47 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/04 13:22:24 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"


void	wall_casting(t_data *data)
{
	
}

static void	x_loop(t_data *data, t_mypov_for_floor me, t_godpov_for_floor god)
{
	int	txX;
	int	txY;
	int	color;

	me.x = 0;
	while (me.x < WIDTH)
	{
		god.mapX = (int)god.floorX;
		god.mapY = (int)god.floorY;
		txX = (int)(BLOCKWIDTH * (god.floorX - god.mapX)) \
						& (BLOCKWIDTH - 1);
		txY = (int)(BLOCKHEIGHT * (god.floorY - god.mapY)) \
						& (BLOCKHEIGHT - 1);
		color = data->texture[FLOOR_NUM][BLOCKWIDTH * txY + txX];
		data->buf[me.y][me.x] = color;
		color = data->texture[CEILING_NUM][BLOCKHEIGHT * txY + txY];
		data->buf[HEIGHT - me.y - 1][me.x] = color;
		me.x += 1;
		god.floorX += god.stepX;
		god.floorY += god.stepY;
	}
}

void	floor_ceiling_casting(t_data *data)
{
	t_mypov_for_floor	me;
	t_godpov_for_floor	god;

	me.y = HEIGHT / 2;
	while (++me.y < HEIGHT)
	{
		me.rayXL = data->dirX - data->planeX;
		me.rayXR = data->dirX + data->planeX;
		me.rayYL = data->dirY - data->planeY;
		me.rayYR = data->dirY + data->planeY;
		me.relative_y = me.y - HEIGHT / 2;
		me.posZ = 0.5 * HEIGHT;
		me.rowDistance = me.posZ / me.relative_y;
		god.stepX = me.rowDistance * (me.rayXR - me.rayXL) / WIDTH;
		god.stepY = me.rowDistance * (me.rayYR - me.rayYL) / WIDTH;
		god.floorX = data->posX + me.rowDistance * me.rayXL;
		god.floorY = data->posY + me.rowDistance * me.rayYL;
		x_loop(data, me, god);
	}
}
