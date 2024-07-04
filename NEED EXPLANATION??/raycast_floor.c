/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:20:47 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/04 19:00:28 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void	x_loop(t_data *data, t_mypov4floor me, t_godpov4floor god)
{
	int	txX;
	int	txY;
	int	color;

	me.x = 0;
	while (me.x < WIDTH)
	{
		//その座標から、指している点のマップの座標も見つける
		god.mapX = (int)god.floorX;
		god.mapY = (int)god.floorY;
		//以上を用いて、テクスチャ座標を計算し、その点の色を取得する
		txX = (int)(BLOCKWIDTH * (god.floorX - god.mapX)) \
						& (BLOCKWIDTH - 1);
		txY = (int)(BLOCKHEIGHT * (god.floorY - god.mapY)) \
						& (BLOCKHEIGHT - 1);
		//ビット計算については、基本行われないが63を超えた際に０に戻ってくる
		//カラー変数にテクスチャ座標から色の情報を代入し、それを出力用のbuffに代入
		color = data->texture[FLOOR_NUM][BLOCKWIDTH * txY + txX];
		data->buf[me.y][me.x] = color;
		color = data->texture[CEILING_NUM][BLOCKHEIGHT * txY + txY];
		data->buf[HEIGHT - me.y - 1][me.x] = color;
		//インクリメントする
		me.x += 1;
		god.floorX += god.v_stepX;
		god.floorY += god.v_stepY;
	}
}

void	floor_ceiling_casting(t_data *data)
{
	t_mypov4floor	me;
	t_godpov4floor	god;

	me.y = HEIGHT / 2; //床と天井のキャストは画面の中央を境目に分かれてる
	while (++me.y < HEIGHT)
	{
		//カメラから出るレイの方向のベクトル。左端、右端ともにだす
		//このレイの中にある部分が司会の範囲内
		god.v_rayXL = data->v_dirX - data->v_planeX;
		god.v_rayXR = data->v_dirX + data->v_planeX;
		god.v_rayYL = data->v_dirY - data->v_planeY;
		god.v_rayYR = data->v_dirY + data->v_planeY;
		//中心線に基準を置き、そこからの相対的な距離を計測
		me.relative_y = me.y - HEIGHT / 2;
		//カメラの高さを設定。天井と床の中心
		me.posZ = 0.5 * HEIGHT;
		//現在のrelative_yが指している床の部分の距離が、基準距離の何倍かを計測する
		//画面の下端はこれが１となり、現在地から床の下端までの距離が基準距離にとなる
		me.rowDistance = me.posZ / me.relative_y;
		//画面左端と右端のレイの方向ベクトルの変化量を計測し、幅で割ることで、１ピクセルあたりの変化量
		//rowDitanceにかけることで、relative_yの地点に対応した距離にスケーリングする
		//その結果が、各ピクセルの相対的な位置変化となる
		god.v_stepX = me.rowDistance * (god.v_rayXR - god.v_rayXL) / WIDTH;
		god.v_stepY = me.rowDistance * (god.v_rayYR - god.v_rayYL) / WIDTH;
		//yが現在指す場所の床の座標を計算する
		god.floorX = data->posX + me.rowDistance * god.v_rayXL;
		god.floorY = data->posY + me.rowDistance * god.v_rayYL;
		x_loop(data, me, god);
	}
}
