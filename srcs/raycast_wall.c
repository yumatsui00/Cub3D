/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:55:57 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/04 19:47:36 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void	ray_kees_going(t_data *data, t_godpov4wall *god)
{
	int	reach_wall;

	reach_wall = 0;
	while (!reach_wall)
	{
		if (god->sideDistX < god->sideDistY)
		{
			god->sideDistX += god->cellDistX;
			god->mapX += god->stepX;
			god->EastWestFlag = 0;
		}
		else
		{
			god->sideDistY += god->cellDistY;
			god->mapY += god->stepY;
			god->EastWestFlag = 1;
		}
		if (data->map[god->mapX][god->mapY] > 0)
			reach_wall = 1;
	}
}

static void	measure_dist2wall(t_data *data, t_mypov4wall *me, t_godpov4wall *god)
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
	ray_keeps_going(data, god);
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
		if (god.EastWestFlag == 0)
			god.holizDist = (god.mapX - data->posX + (1 - god.stepX) / 2) / god.v_rayX;
		else
			god.holizDist = (god.mapY - data->posY + (1 - god.stepY) / 2) / god.v_rayX;
		
	}
}