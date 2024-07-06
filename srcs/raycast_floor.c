/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:20:47 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/06 18:35:45 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void	x_loop(t_data *data, t_mypov4floor me, t_godpov4floor god)
{
	int	txX;
	int	txY;
	int	color;

	me.x = 0;
	while (++me.x < WIDTH)
	{
		txX = (int)(BLOCKWIDTH * (god.floorX - floor(god.floorX))) \
						& (BLOCKWIDTH - 1);
		txY = (int)(BLOCKHEIGHT * (god.floorY - floor(god.floorY))) \
						& (BLOCKHEIGHT - 1);
		color = data->texture[FLOOR_NUM][BLOCKWIDTH * txY + txX];
		data->buf[me.y][me.x] = color;
		color = data->texture[CEILING_NUM][BLOCKHEIGHT * txY + txY];
		data->buf[HEIGHT - me.y - 1][me.x] = color;
		god.floorX += god.v_stepX;
		god.floorY += god.v_stepY;
	}
}

void	floor_ceiling_casting(t_data *data)
{
	t_mypov4floor	me;
	t_godpov4floor	god;

	me.y = HEIGHT / 2 + 1;
	while (++me.y < HEIGHT)
	{
		god.v_rayXL = data->v_dirX - data->v_planeX;
		god.v_rayXR = data->v_dirX + data->v_planeX;
		god.v_rayYL = data->v_dirY - data->v_planeY;
		god.v_rayYR = data->v_dirY + data->v_planeY;
		me.relative_y = me.y - HEIGHT / 2;
		me.posZ = 0.5 * HEIGHT;
		me.rowDistance = me.posZ / me.relative_y;
		god.v_stepX = me.rowDistance * (god.v_rayXR - god.v_rayXL) / WIDTH;
		god.v_stepY = me.rowDistance * (god.v_rayYR - god.v_rayYL) / WIDTH;
		god.floorX = data->posX + me.rowDistance * god.v_rayXL;
		god.floorY = data->posY + me.rowDistance * god.v_rayYL;
		x_loop(data, me, god);
	}
}
