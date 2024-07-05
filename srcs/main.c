/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:04:31 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/05 19:31:53 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int main(void) {
	t_data	data;

	//! マップ解析必要です

	if (init_data(&data) == MALLOCERROR)
		return (MALLOCERROR);

	//* 以上小松

	data.key_a = 0;
	data.key_w = 0;
	data.key_s = 0;
	data.key_d = 0;
	data.key_esc = 0;
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3D");
	data.img.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.img.info = (int *)mlx_get_data_addr(data.img.img, &data.img.bpp, &data.img.size_l, &data.img.endian);
	mlx_loop_hook(data.mlx, &mainloop_perflame, &data);
	mlx_hook(data.win, KEY_PRESS, 0, &key_press, &data);
	mlx_hook(data.win, KEY_RELEASE, 0, &key_release, &data);
	mlx_loop(data.mlx);
}
