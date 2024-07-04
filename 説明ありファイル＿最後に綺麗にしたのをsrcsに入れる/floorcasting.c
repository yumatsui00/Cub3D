/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:13:45 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/04 13:18:07 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	floorcasting(t_data *data)
{
	t_cal	cal;

	cal.y = HEIGHT / 2;
	//以降は基本カメラ目線で
	//最大で画面の下半分に床が描画されるため、半分以上（y軸は下が正）
	while (++cal.y < HEIGHT)
	{
		// 画面の左端と右端のレイの方向ベクトル計算
		// カメラ（自分）からレイを照射ており、それの左端、右端の方向ベクトル
		cal.rayDirXLeft = data->dirX - data->planeX;
		cal.rayDirXRight = data->dirX + data->planeX;
		cal.rayDirYLeft = data->dirY - data->planeY;
		cal.rayDirYRight = data->dirY + data->planeY;
		//スクリーン中の現在のy座標（地平線を０とした場合）
		cal.currenty = cal.y - HEIGHT / 2;
		//カメラの高さ（天井と床の真ん中にあると設定）
		cal.posZ = 0.5 * HEIGHT;
		//現在地から、現在のyが指している床の地点までの距離を測定する
		//currenty = 0 == 地平線　の時は無限大（本来は特別な処理になる）
		//例えば、rowDistance = 2の時、そのyが指す床までの距離は、基準距離の２倍の距離となる
		//カメラ下端を調べるとrowistance = 1 となり、イメージとしてはそこまでの距離が下端距離。今回は天井と床の中央にカメラを設置しているのでわかりやすい
		cal.rowDistance = cal.posZ / cal.currenty;
		//画面左端と右端のレイの方向ベクトルをのの変化量を計算し、それをピクセル毎に分割する
		//rowDistance をかけ、currentyに対応した距離にスケーリングする
		//これにより、各ピクセルの相対的な位置変化を計算し、床のどの部分を示すべきかを計算し、正確な床の描写を可能にしている
		cal.floorStepX = cal.rowDistance * (cal.rayDirXRight - cal.rayDirXLeft) / WIDTH;
		cal.floorStepY = cal.rowDistance * (cal.rayDirYRight - cal.rayDirYLeft) / WIDTH;
		//現在地に基づいて、currentyが指している床の、実際のマップの座標を計算
		//描画する際に、 フロアステップベクトルを用いて計算を行なっていくため、左端のレイベクトルを用いて初期化
		//!これはカメラ目線の座標じゃない
		cal.floorX = data->posX + cal.rowDistance * cal.rayDirXLeft;
		cal.floorY = data->posY + cal.rowDistance * cal.rayDirXLeft;
		cal.x = -1;
		while (++cal.x < WIDTH)
		{
			//現在の座標が、マップ座標系のどの位置に対応しているか特定する
			cal.cellX = (int)cal.floorX;
			cal.cellY = (int)cal.floorY;
			//現在のピクセルに対応する床のテクスチャ内のテクスチャ座標を計算し、そこの色を取得するための準備をする
			//ビット計算は、基本ないが、右辺の１項が６３を超えた時に循環して戻ってくるように
			cal.tx = (int)(BLOCKWIDTH * (cal.floorX - cal.cellX)) & (BLOCKWIDTH - 1);
			cal.ty = (int)(BLOCKHEIGHT * (cal.floorX - cal.cellY)) & (BLOCKHEIGHT - 1);
			//テクスチャ座標もわかったので、次に進めておく
			cal.floorX += cal.floorStepX;
			cal.floorY += cal.floorStepY;
			//カラー変数に、テクスチャの座標から色を取ってきて代入、それを出力用のバッファに入れる
			//天井は上下対称なだけなので、同時に行う.
			//!こっちでプログラムうごかしたかったら以下を治す必要あり
			cal.color = data->texture[FLOOR_NUM][BLOCKWIDTH * txY + txX];
			data->buf[me.y][me.x] = color;
			color = data->texture[CEILING_NUM][BLOCKHEIGHT * txY + txY];
			data->buf[HEIGHT - me.y - 1][me.x] = color;
			me.x += 1;
			god.floorX += god.stepX;
			god.floorY += god.stepY;
		}
	}
}
