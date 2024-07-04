/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:04:31 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/04 10:03:33 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int main(void) {
	t_data	data;

	//! マップ解析必要です

	if (init_data(&data) == MALLOCERROR)
		return (MALLOCERROR);

	//* 以上小松


	//data.mlx = init info(return value of mlx_init())
	//!ウィンドウを作成し、そのポインターを返す　
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3D");
	//!指定されたサイズのバッファを作成し、画像のポインタを返す
	data.img.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	//img.bpp: 画像で１ピクセル毎のビット数を格納したポインタ
	//img.size_l:１行ごとのバイト数を格納したポインタ
	//img.endian: 色のつけ方についての情報を格納している
	//!指定された画像のアドレスを獲得し、画像の最初のピクセルのポインタを返す
	data.img.info = (int *)mlx_get_data_addr(data.img.img, &data.img.bpp, &data.img.size_l, &data.img.endian);

	mlx_loop_hook(data.mlx, &mainloop_perflame, &data);

}