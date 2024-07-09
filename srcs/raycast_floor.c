/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:20:47 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/09 14:20:05 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

static int	change_color(int  color, t_data *data, int c_or_f)
{
	int		ret;
	t_rgb	palette;

	if (c_or_f == FLOOR_NUM)
		palette = data->f_rgb;
	else
		palette = data->c_rgb;
	ret = color;
	ret += (palette.r << 16);
	ret += (palette.g << 8);
	ret += palette.b;
	return (ret);
}

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
		color = change_color(color, data, FLOOR_NUM);
		data->buf[me->y][me->x] = color;
		color = data->texture[CEILING_NUM][BLOCKHEIGHT * tx_y + tx_x];
		color = change_color(color, data, CEILING_NUM);
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
		god.v_ray_xl = data->v_dir_x - data->v_plane_x;
		god.v_ray_xr = data->v_dir_x + data->v_plane_x;
		god.v_ray_yl = data->v_dir_y - data->v_plane_y;
		god.v_ray_yr = data->v_dir_y + data->v_plane_y;
		me.relative_y = me.y - HEIGHT / 2;
		me.pos_z = 0.5 * HEIGHT;
		me.row_distance = me.pos_z / me.relative_y;
		god.v_step_x = me.row_distance * (god.v_ray_xr - god.v_ray_xl) / WIDTH;
		god.v_step_y = me.row_distance * (god.v_ray_yr - god.v_ray_yl) / WIDTH;
		god.floor_x = data->pos_x + me.row_distance * god.v_ray_xl;
		god.floor_y = data->pos_y + me.row_distance * god.v_ray_yl;
		x_loop(data, &me, &god);
	}
}
