/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:20:47 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/08 14:26:41 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void	x_loop(t_data *data, t_mypov4floor *me, t_godpov4floor *god)
{
	int	tx_x;
	int	tx_y;
	int	color;
	int	cell_x;
	int	cell_y;

	me->x = 0;
	while (++me->x < WIDTH)
	{
		cell_x = (int)(god->floor_x);
		cell_y = (int)(god->floor_y);
		tx_x = (int)(BLOCKWIDTH * (god->floor_x - cell_x)) \
						& (BLOCKWIDTH - 1);
		tx_y = (int)(BLOCKHEIGHT * (god->floor_y - cell_y)) \
						& (BLOCKHEIGHT - 1);
		color = data->texture[FLOOR_NUM][BLOCKWIDTH * tx_y + tx_x];
		data->buf[me->y][me->x] = color;
		color = data->texture[CEILING_NUM][BLOCKHEIGHT * tx_y + tx_x];
		data->buf[HEIGHT - me->y - 1][me->x] = color;
		god->floor_x += god->v_step_x;
		god->floor_y += god->v_step_y;
	}
}

void	floor_ceiling_casting(t_data *data)
{
	t_mypov4floor	me;
	t_godpov4floor	god;

	me.y = HEIGHT / 2;
	while (++me.y < HEIGHT)
	{
		god.v_ray_xl = data->v_dirX - data->v_planeX;
		god.v_ray_xr = data->v_dirX + data->v_planeX;
		god.v_ray_yl = data->v_dirY - data->v_planeY;
		god.v_ray_yr = data->v_dirY + data->v_planeY;
		me.relative_y = me.y - HEIGHT / 2;
		me.pos_z = 0.5 * HEIGHT;
		me.row_distance = me.pos_z / me.relative_y;
		god.v_step_x = me.row_distance * (god.v_ray_xr - god.v_ray_xl) / WIDTH;
		god.v_step_y = me.row_distance * (god.v_ray_yr - god.v_ray_yl) / WIDTH;
		god.floor_x = data->posX + me.row_distance * god.v_ray_xl;
		god.floor_y = data->posY + me.row_distance * god.v_ray_yl;
		x_loop(data, &me, &god);
	}
}
