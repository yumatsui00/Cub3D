/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:55:57 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/04 21:46:17 by yumatsui         ###   ########.fr       */
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
//! ウォールキャストとフロアキャストは、キャストの方法がそもそも異なる
//! フロアキャストはy座標ごとに包括的なキャストが可能だが、ウォールキャストはピクセルごとのキャストが必要
void	wall_casting(t_data *data)
{
	//me：カメラ目線でのx, y座標
	//god: マップを上から見た時のx、y座標
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
		//壁までの垂直距離（水平に距離を測った時の距離）を計測する
		//壁の上下などは中心に比べて距離が長いため、魚眼効果が発生してしまうので、それを防ぐため
		//　v_rayで割ればよく、（1-god.stepX ）の部分は、壁の位置補正をしている。
		//例えば壁に右から当たるときは問題ないが、二次元配列の構造上、左から当たるときはさらに一つ進まないといけないのでそれを補正している
		if (god.NorthSouthFlag == 0)
			god.holizDist = (god.mapX - data->posX + (1 - god.stepX) / 2) / god.v_rayX;
		else
			god.holizDist = (god.mapY - data->posY + (1 - god.stepY) / 2) / god.v_rayX;
		//壁までの距離によって、壁の見え方（大きさ）が変わってくるので、その計算
		me.wallheight = (int)(HEIGHT / god.holizDist);
		//y座標における、壁の描き出し描き終わりを調べる
		me.wallUpperEdge = (HEIGHT / 2) - (me.wallheight / 2);
		if (me.wallUpperEdge < 0)
			me.wallUpperEdge = 0;
		me.wallLowerEdge = (HEIGHT / 2) + (me.wallheight / 2);
		if (me.wallLowerEdge >= HEIGHT)
			me.wallUpperEdge = HEIGHT - 1;
		// 壁のtexture座標のx座標を調べる(0.2みたいな%で算出)
		int wallX;
		//EorWに当たるときは、y座標を調べて、小数点以下を見れば良い。NSはx
		if (god.NorthSouthFlag == 0)
			wallX = data->posY + god.holizDist * god.v_rayY;
		else
			wallX = data->posX + god.holizDist * god.v_rayX;
		wallX -= floor(wallX);
		int	txX = (int)(wallX * (double)BLOCKHEIGHT);
		//西側、北側の壁は左右反転させる
		if (god.NorthSouthFlag == 0 && god.v_rayX > 0 || god.NorthSouthFlag == 1 && god.v_rayY < 0)
			txX = BLOCKWIDTH - txX - 1;
		//１画面ピクセルで、テクスチャ座標がどれだけ増加するか調べる
		double	step;
		step = BLOCKHEIGHT / me.wallheight;
		//テクスチャの初期座標を決定
		double	txstart;
		txstart = (me.wallUpperEdge - HEIGHT / 2 + BLOCKHEIGHT / 2) * step;
		me.y = me.wallUpperEdge;
		while (me.y < me.wallLowerEdge)
		{
			int	txY = (int)txstart & (BLOCKHEIGHT - 1);
			int color = data->texture[ここに壁紙番号（東西南北）][BLOCKHEIGHT * txY + txX];
			data->buf[me.y][me.x] = color;
			me.y++;
			txstart += step;
		}
		// data->zBuffer[me.z] = god.holizDist; spriteなしなら要らない

	}
}
