/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:20:47 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/04 16:09:28 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	measure_dist2wall(t_data *data, t_mypov4wall *me, t_godpov4wall *god)
{
	if (god->v_rayX < 0)
	{
		god->stepX = -1;
		god->sideDistX = (data->posX - god->mapX) * god->cellDistX;
	}
	else
	{
		god->stepX = 1;
		god->sideDistX = (god->mapX + 1 - data->posX) * god->cellDistX;
	}
	if (god->v_rayY < 0)
	{
		god->stepY = -1;
		god->sideDistY = (data->posY - god->mapY) * god->cellDistY;
	}
	else
	{
		god->stepY = 1;
		god->sideDistY = (god->mapY + 1 - data->posX) * god->cellDistX;
	}
}

void	wall_casting(t_data *data)
{
	t_mypov4wall	me;
	t_godpov4wall	god;

	me.x = -1;
	while (++me.x < WIDTH)
	{
		me.camX = 2 * me.x / (double)WIDTH - 1;
		god.v_rayX = data->v_dirX + data->v_planeX * me.camX;
		god.v_rayY = data->v_dirY + data->v_planeY * me.camX;
		god.cellDistX = fabs(1 / god.v_rayX);
		god.cellDistY = fabs(1 / god.v_rayX);
		god.mapX = (int)data->posX;
		god.mapY = (int)data->posY;
		measure_dist2wall(data, &me, &god);
	}
}

static void	x_loop(t_data *data, t_mypov4floor me, t_godpov4floor god)
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
		god.floorX += god.v_stepX;
		god.floorY += god.v_stepY;
	}
}

void	floor_ceiling_casting(t_data *data)
{
	t_mypov4floor	me;
	t_godpov4floor	god;

	me.y = HEIGHT / 2;
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
