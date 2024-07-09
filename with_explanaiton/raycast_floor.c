/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:20:47 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/09 15:15:35 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

static int	change_color(int color, t_data *data, int c_or_f)
{
	int		ret;
	t_rgb	palette;

	if (c_or_f == FLOOR_NUM)
		palette = data->f_rgb;
	else
		palette = data->c_rgb;
	ret = color;
	//for color red
	ret += (palette.r << 16);
	//for color green
	ret += (palette.g << 8);
	//for color blue
	ret += palette.b;
	return (ret);
}

static void	x_loop(t_data *data, t_mypov4floor *me, t_godpov4floor *god)
{
	int	tx_x;
	int	tx_y;
	int	color;
	//3 factors above are used when draw textures
	int	cell_x;
	int	cell_y;

	me->x = 0;
	while (++me->x < WIDTH)
	{
		//calculate where the current point is in texture coordinates
		cell_x = (int)(god->floor_x);
		cell_y = (int)(god->floor_y);
		tx_x = (int)(BLOCKWIDTH * (god->floor_x - cell_x)) \
						& (BLOCKWIDTH - 1);
		tx_y = (int)(BLOCKHEIGHT * (god->floor_y - cell_y)) \
						& (BLOCKHEIGHT - 1);
		//get the color of the point of the floor texture
		color = data->texture[FLOOR_NUM][BLOCKWIDTH * tx_y + tx_x];
		//change color as the subject says
		color = change_color(color, data, FLOOR_NUM);
		//store it in the buf which you output afterwards
		data->buf[me->y][me->x] = color;
		//*the floor and ceiling are vertically symmetrical
		color = data->texture[CEILING_NUM][BLOCKHEIGHT * tx_y + tx_x];
		color = change_color(color, data, CEILING_NUM);
		data->buf[HEIGHT - me->y - 1][me->x] = color;
		//increment, and proceed to the next step
		god->floor_x += god->v_step_x;
		god->floor_y += god->v_step_y;
	}
}

void	floor_ceiling_casting(t_data *data)
{
	//! me: the coordinates in the player's POV in the game. what you see on the screen while playing.
	//! god: the coordinates when viewing the map from above
	//! Variables with the prefix "v_" are vector

	t_mypov4floor	me;
	t_godpov4floor	god;

	me.y = HEIGHT / 2;//these casts are separated by a line deviding the screen into upper and lower halves
	while (++me.y < HEIGHT)
	{
		//The dirction vectors of the ray. specifically, the left and right edges of me POV.
		god.v_ray_xl = data->v_dir_x - data->v_plane_x;
		god.v_ray_xr = data->v_dir_x + data->v_plane_x;
		god.v_ray_yl = data->v_dir_y - data->v_plane_y;
		god.v_ray_yr = data->v_dir_y + data->v_plane_y;
		//The distance between current y to center line in pixel scale.
		me.relative_y = me.y - HEIGHT / 2;
		//The hight of me POV camera. placed in the center for clarity.
		me.pos_z = 0.5 * HEIGHT;
		//Horizontal distance from the camera to the floor for the current row
		me.row_distance = me.pos_z / me.relative_y;
		//step vector from above. parallel to plane vecor
		god.v_step_x = me.row_distance * (god.v_ray_xr - god.v_ray_xl) / WIDTH;
		god.v_step_y = me.row_distance * (god.v_ray_yr - god.v_ray_yl) / WIDTH;
		// coordinate in the map. will be updated at each step.
		god.floor_x = data->pos_x + me.row_distance * god.v_ray_xl;
		god.floor_y = data->pos_y + me.row_distance * god.v_ray_yl;
		x_loop(data, &me, &god);
	}
}
