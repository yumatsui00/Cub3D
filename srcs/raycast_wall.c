/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:55:57 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/06 18:24:04 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void	ray_keeps_going(t_data *data, t_godpov4wall *god)
{
	int	reach_wall;

	reach_wall = 0;
	while (!reach_wall)
	{
		if (god->sideDistX < god->sideDistY)
		{
			god->sideDistX += god->cellDistX;
			god->mapX += god->stepX;
			god->NorthSouthFlag = 0;
		}
		else
		{
			god->sideDistY += god->cellDistY;
			god->mapY += god->stepY;
			god->NorthSouthFlag = 1;
		}
		// printf("x = %d, y = %d\n", god->mapX, god->mapY);
		// debug_intmap(data->map);
		// printf("%d\n", data->map[god->mapY][god->mapX]);
		// printf("exitするよ\n");
		// exit(0);
		
		if (data->map[god->mapY][god->mapX] > 0)
			reach_wall = 1;
	}
}

static void	rays_hit_which_side(t_data *data, t_mypov4wall *me, t_godpov4wall *god)
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

static void buf_update(t_data *data, t_mypov4wall *me, t_godpov4wall *god, t_tx tx)
{
	me->y = me->wallUpperEdge;
	if (god->NorthSouthFlag == 1 && god->v_rayY > 0)
		tx.num = WALLNORTH_NUM;
	else if (god->NorthSouthFlag == 1 && god->v_rayY < 0)
		tx.num = WALLSOUTH_NUM;
	else if (god->NorthSouthFlag == 0 && god->v_rayX > 1)
		tx.num = WALLWEST_NUM;
	else
		tx.num = WALLEAST_NUM;
	while (me->y < me->wallLowerEdge)
	{
		tx.y = (int)tx.start & (BLOCKHEIGHT - 1);
		tx.color = data->texture[tx.num][BLOCKHEIGHT * tx.x + tx.y];
		data->buf[me->y][me->x] = tx.color;
		me->y++;
		tx.start += tx.step;
	}
}

static void	wall_casting2(t_data *data, t_mypov4wall *me, t_godpov4wall *god)
{
	t_tx	tx;

	if (god->NorthSouthFlag == 0)
		god->holizDist = (god->mapX - data->posX + (1 - god->stepX) / 2) / 1;//god->v_rayX;
	else
		god->holizDist = (god->mapY - data->posY + (1 - god->stepY) / 2) / 1;//god->v_rayY;
	me->wallheight = (int)(HEIGHT / god->holizDist);
	me->wallUpperEdge = (HEIGHT / 2) - (me->wallheight / 2);
	if (me->wallLowerEdge < 0)
		me->wallUpperEdge = 0;
	me->wallLowerEdge = (HEIGHT / 2) + (me->wallheight / 2);
	if (me->wallLowerEdge > HEIGHT - 1)
		me->wallheight = HEIGHT - 1;
	if (god->NorthSouthFlag)
		tx.wallX = data->posY + god->holizDist * god->v_rayY;
	else
		tx.wallX = data->posX + god->holizDist * god->v_rayX;
	tx.wallX -= floor(tx.wallX);
	//西側、北側の壁は左右反転させる
	// if (god->NorthSouthFlag == 0 && god->v_rayX > 0 || god->NorthSouthFlag == 1 && god->v_rayY < 0)
	// 	txX = BLOCKWIDTH - txX - 1;
	tx.step = BLOCKHEIGHT / me->wallheight;
	tx.start = (me->wallUpperEdge - HEIGHT / 2 + BLOCKHEIGHT / 2) * tx.step;
	buf_update(data, me, god, tx);
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
		rays_hit_which_side(data, &me, &god);
		wall_casting2(data, &me, &god);
	}
	// printf("kkk\n");
	// exit(0);
}
