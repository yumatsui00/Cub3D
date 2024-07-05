/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:20:47 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/06 06:10:43 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void	x_loop(t_data *data, t_mypov4floor me, t_godpov4floor god)
{
	//3 factors below are used when draw textures
	int	txX;
	int	txY;
	int	color;

	me.x = 0;
	while (me.x < WIDTH)
	{
		//calculate where the current point is in texture coordinates
		txX = (int)(BLOCKWIDTH * (god.floorX - floor(god.floorX))) \
						& (BLOCKWIDTH - 1);
		txY = (int)(BLOCKHEIGHT * (god.floorY - floor(god.floorY))) \
						& (BLOCKHEIGHT - 1);
		//get the color of the point of the floor texture
		color = data->texture[FLOOR_NUM][BLOCKWIDTH * txY + txX];
		//store it in the buf which you output afterwards
		data->buf[me.y][me.x] = color;
		//*the floor and ceiling are vertically symmetrical
		color = data->texture[CEILING_NUM][BLOCKHEIGHT * txY + txY];
		data->buf[HEIGHT - me.y - 1][me.x] = color;
		//increment, and proceed to the next step
		me.x += 1;
		god.floorX += god.v_stepX;
		god.floorY += god.v_stepY;
	}
}

void	floor_ceiling_casting(t_data *data)
{
	t_mypov4floor	me;
	t_godpov4floor	god;

	//! me: the coordinates in the player's POV in the game. what you see on the screen while playing.
	//! god: the coordinates when viewing the map from above
	//! Variables with the prefix "v_" are vector

	me.y = HEIGHT / 2; //these casts are separated by a line deviding the screen into upper and lower halves
	while (++me.y < HEIGHT)
	{
		//The dirction vectors of the ray. specifically, the left and right edges of me POV.
		god.v_rayXL = data->v_dirX - data->v_planeX;
		god.v_rayXR = data->v_dirX + data->v_planeX;
		god.v_rayYL = data->v_dirY - data->v_planeY;
		god.v_rayYR = data->v_dirY + data->v_planeY;
		//The distance between current y to center line in pixel scale.
		me.relative_y = me.y - HEIGHT / 2;
		//The hight of me POV camera. placed in the center for clarity.
		me.posZ = 0.5 * HEIGHT;
		//Horizontal distance from the camera to the floor for the current row
		me.rowDistance = me.posZ / me.relative_y;
		//step vector from above. parallel to plane vecor
		god.v_stepX = me.rowDistance * (god.v_rayXR - god.v_rayXL) / WIDTH;
		god.v_stepY = me.rowDistance * (god.v_rayYR - god.v_rayYL) / WIDTH;
		// coordinate in the map. will be updated at each step.
		god.floorX = data->posX + me.rowDistance * god.v_rayXL;
		god.floorY = data->posY + me.rowDistance * god.v_rayYL;
		x_loop(data, me, god);
	}
}
