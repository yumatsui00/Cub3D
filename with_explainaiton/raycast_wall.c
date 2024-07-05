/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:55:57 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/06 07:35:37 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void	ray_kees_going(t_data *data, t_godpov4wall *god)
{
	int	reach_wall;
	//check in order from the nearest boundary since the wall is ajadcent to the cell boundary
	//mostly, rays don't travel parallel to the x or y-axis. (they do diagonally)
	//so, you have to check which wall the ray hits first. and i did it as below
	reach_wall = 0;
	while (!reach_wall)
	{
		if (god->sideDistX < god->sideDistY)
		{
			god->sideDistX += god->cellDistX;
			//also update mapX to the coordinates of the wall hit by the ray
			god->mapX += god->stepX;
			// Don't forget to set a flag ;(
			god->NorthSouthFlag = 0;
		}
		else
		{
			god->sideDistY += god->cellDistY;
			god->mapY += god->stepY;
			god->NorthSouthFlag = 1;
		}
		if (data->map[god->mapX][god->mapY] > 0)
			reach_wall = 1;
	}
}

static void	rays_hit_which_side(t_data *data, t_mypov4wall *me, t_godpov4wall *god)
{
	//classify the direction of the ray into 1st to 4th quadrant
	if (god->v_rayX < 0)
	{
		//the direction of ray's step!
		god->stepX = -1;
		//determine the num of vectors needed to reach the closest cell x boundary from current position
		god->sideDistX = (data->posX - god->mapX) * god->cellDistX;
	}
	else
	{
		god->stepX = 1;
		god->sideDistX = (god->mapX + 1 - data->posX) * god->cellDistX;
	}
	if (god->v_rayY < 0)
	{
		//same as for x. In the case of y.
		god->stepY = -1;
		god->sideDistY = (data->posY - god->mapY) * god->cellDistY;
	}
	else
	{
		god->stepY = 1;
		god->sideDistY = (god->mapY + 1 - data->posX) * god->cellDistX;
	}
	//Now, sideDist represent the distance from cuurent position to the nearest cell boundary (ofc, x & y hold separate values).
	ray_keeps_going(data, god);
}

static void	buf_update(t_data *data, t_mypov4wall *me, t_godpov4wall *god, t_tx tx)
{
	//only need to update the buf for the part where the wall is rendered
	me->y = me->wallUpperEdge;
	//determine whchi side of the wall you output
	if (god->NorthSouthFlag = 1 && god->v_rayY > 0)
		tx.num = WALLNORTH_NUM;
	else if (god->NorthSouthFlag = 1 && god->v_rayY < 0)
		tx.num = WALLSOUTH_NUM;
	else if (god->NorthSouthFlag = 0 && god->v_rayX > 1)
		tx.num = WALLWEST_NUM;
	else
		tx.num = WALLEAST_NUM;
	while (me->y < me->wallLowerEdge)
	{
		//determine the texture coordinate so you can get color
		tx.y = (int)tx.start & (BLOCKHEIGHT - 1);
		tx.color = data->texture[tx.num][BLOCKHEIGHT * tx.x + tx.y];
		//update buf
		data->buf[me->y][me->x] = tx.color;
		//dont forget increment :)
		me->y++;
		tx.start += tx.step;
	}
}

static void	wall_casting2(t_data *data, t_mypov4wall *me, t_godpov4wall *god)
{
	//tx means texture coordinate
	t_tx	tx;

	// calc the horizontal distance from current location to the wall hit by the ray
	if (god->NorthSouthFlag == 0)
		god->holizDist = (god->mapX - data->posX + (1 - god->stepX) / 2) / god->v_rayX;
	else
		god->holizDist = (god->mapY - data->posY + (1 - god->stepY) / 2) / god->v_rayY;
	// calc the apparent size of the wall based on the distance in pixel scale
	me->wallheight = (int)(HEIGHT / god->holizDist);
	// determine from which pixel you start drawing the wall
	me->wallUpperEdge = (HEIGHT / 2) - (me->wallheight / 2);
	if (me->wallLowerEdge < 0)
		me->wallUpperEdge = 0;
	// determine from which pixel you stop drawing the wall
	me->wallLowerEdge = (HEIGHT / 2) + (me->wallheight / 2);
	if (me->wallLowerEdge > HEIGHT - 1)
		me->wallheight = HEIGHT - 1;
	// determine the x-coordinate on the wall's texture coordinates of the point which the ray reach
	if (god->NorthSouthFlag)
		tx.wallX = data->posY + god->holizDist * god->v_rayY;
	else
		tx.wallX = data->posX + god->holizDist * god->v_rayX;
	tx.wallX -= floor(tx.wallX);
	//↑ calculated as a percentage.

	//!西側、北側の壁は左右反転させる(必要かどうかは要判断)
	// if (god->NorthSouthFlag == 0 && god->v_rayX > 0 || god->NorthSouthFlag == 1 && god->v_rayY < 0)
	// 	txX = BLOCKWIDTH - txX - 1;

	// calc how many pixels one pixel on the screen moves in texture coordinate
	tx.step = BLOCKHEIGHT / me->wallheight;
	// determine the initial coordinates of the texture（the upper edge of the wall might be off-screen）
	tx.start = (me->wallUpperEdge - HEIGHT / 2 + BLOCKHEIGHT / 2) * tx.step;
	buf_update(data, me, god, tx);
}

void	wall_casting(t_data *data)
{
	//will update the buf you filled.
	t_mypov4wall	me;
	t_godpov4wall	god;

	//!first of all, the method of wall and floor raycasting are different.
	//will raycast wall along y-axis though raycasting the floor was along x-axis.
	me.x = -1;
	while (++me.x < WIDTH)
	{
		//Devide me POV Devide me POV into pixels, and assign x_coordinates ranging from -1 to 1
		//so it's easier to calculate :)
		me.camX = 2 * me.x / (double)WIDTH - 1;
		//The vector of ray
		god.v_rayX = data->v_dirX + data->v_planeX * me.camX;
		god.v_rayY = data->v_dirY + data->v_planeY * me.camX;
		//calc how many vectors are needed to move one cell
		god.cellDistX = fabs(1 / god.v_rayX);
		god.cellDistY = fabs(1 / god.v_rayX);
		//check which coordinate of the map you're at.
		god.mapX = (int)data->posX;
		god.mapY = (int)data->posY;
		//calc the distance to wall
		rays_hit_which_side(data, &me, &god);
		wall_casting2(data, &me, &god);
	}
}
