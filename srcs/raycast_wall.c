/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:55:57 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/08 14:33:41 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void	ray_keeps_going(t_data *data, t_godpov4wall *god)
{
	int	reach_wall;

	reach_wall = 0;
	while (!reach_wall)
	{
		if (god->side_dist_x < god->side_dist_y)
		{
			god->side_dist_x += god->cell_dist_x;
			god->map_x += god->step_x;
			god->ns_flag = 0;
		}
		else
		{
			god->side_dist_y += god->cell_dist_y;
			god->map_y += god->step_y;
			god->ns_flag = 1;
		}
		if (data->map[god->map_y][god->map_x] > 0)
			reach_wall = 1;
	}
}

static void	rays_hit_which_side(t_data *data, t_mypov4wall *me,
		t_godpov4wall *god)
{
	if (god->v_ray_x < 0)
	{
		god->step_x = -1;
		god->side_dist_x = (data->posX - god->map_x) * god->cell_dist_x;
	}
	else
	{
		god->step_x = 1;
		god->side_dist_x = (god->map_x + 1.0 - data->posX) * god->cell_dist_x;
	}
	if (god->v_ray_y < 0)
	{
		god->step_y = -1;
		god->side_dist_y = (data->posY - god->map_y) * god->cell_dist_y;
	}
	else
	{
		god->step_y = 1;
		god->side_dist_y = (god->map_y + 1 - data->posY) * god->cell_dist_y;
	}
	//!この辺りで開閉するドアの処理、当たってドアだったら開ける
	//ペラペラなら0.５でいけるから楽やねんけどな
	ray_keeps_going(data, god);
}

static void	buf_update(t_data *data, t_mypov4wall *me, t_godpov4wall *god,
		t_tx tx)
{
	tx.wall_x -= floor(tx.wall_x);
	tx.x = (int)(tx.wall_x * (double)BLOCKWIDTH);
	if (god->ns_flag == 1 && god->v_ray_y > 0)
		tx.num = WALLNORTH_NUM;
	else if (god->ns_flag == 1 && god->v_ray_y <= 0)
		tx.num = WALLSOUTH_NUM;
	else if (god->ns_flag == 0 && god->v_ray_x > 0)
		tx.num = WALLWEST_NUM;
	else
		tx.num = WALLEAST_NUM;
	me->y = me->wall_u_edge;
	while (me->y < me->wall_l_edge)
	{
		if (me->y < HEIGHT)
		{//!このif分がないと壁に近づくとクラッシュ
			tx.y = (int)tx.start & (BLOCKHEIGHT - 1);
			tx.color = data->texture[tx.num][BLOCKHEIGHT * tx.y + tx.x];
			data->buf[me->y][me->x] = tx.color;
		}
		me->y++;
		tx.start += tx.step;
	}
}

static void	wall_casting2(t_data *data, t_mypov4wall *me, t_godpov4wall *god)
{
	t_tx	tx;

	if (god->ns_flag == 0)
		god->holiz_dist = (god->map_x - data->posX + (1 - god->step_x) / 2)
			/ god->v_ray_x;
	else
		god->holiz_dist = (god->map_y - data->posY + (1 - god->step_y) / 2)
			/ god->v_ray_y;
	me->wallheight = (int)(HEIGHT / god->holiz_dist);
	me->wall_u_edge = (HEIGHT / 2) - (me->wallheight / 2);
	tx.step = (double)BLOCKHEIGHT / (double)me->wallheight;
	if (me->wall_u_edge < 0)
		tx.start = (me->wallheight / 2 - HEIGHT / 2) * tx.step;
	else
		tx.start = 0;
	if (me->wall_u_edge < 0)
		me->wall_u_edge = 0;
	me->wall_l_edge = (HEIGHT / 2) + (me->wallheight / 2);
	if (me->wall_l_edge >= HEIGHT)
		me->wallheight = HEIGHT - 1;
	if (!god->ns_flag)
		tx.wall_x = data->posY + god->holiz_dist * god->v_ray_y;
	else
		tx.wall_x = data->posX + god->holiz_dist * god->v_ray_x;
	//西側、北側の壁は左右反転させる
	// if ((god->ns_flag == 0 && god->v_ray_x > 0) || (god->ns_flag == 1
	// 		&& god->v_ray_y < 0))
	// 	tx.x = BLOCKWIDTH - tx.x - 1;
	buf_update(data, me, god, tx);
}

void	wall_casting(t_data *data)
{
	t_mypov4wall	me;
	t_godpov4wall	god;

	me.x = -1;
	while (++me.x < WIDTH)
	{
		me.cam_x = 2 * me.x / (double)WIDTH - 1;
		god.v_ray_x = data->v_dirX + data->v_planeX * me.cam_x;
		god.v_ray_y = data->v_dirY + data->v_planeY * me.cam_x;
		god.cell_dist_x = fabs(1 / god.v_ray_x);
		god.cell_dist_y = fabs(1 / god.v_ray_y);
		god.map_x = (int)data->posX;
		god.map_y = (int)data->posY;
		rays_hit_which_side(data, &me, &god);
		wall_casting2(data, &me, &god);
	}
}
