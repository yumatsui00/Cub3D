/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:04:31 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/03 19:49:00 by yumatsui         ###   ########.fr       */
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
	//!creat a winow, return a ptr of the window　
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3D");
	//!creat a buff of a spwcified size, return a ptr of img buff.
	data.img.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	//img.bpp: ptr to store the num of bits per pixel in the image
	//img.size_l: ptr to store the num of byte per line
	//img.endian: 色のつけ方についての情報を格納している
	//!get data addr of a specified image, and detail, return a ptr of first pixel of the image
	data.img.info = (int *)mlx_get_data_addr(data.img.img, &data.img.bpp, &data.img.size_l, &data.img.endian);
	

}