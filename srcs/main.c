/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:04:31 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/07 14:27:37 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	printall(t_data data)
{
	printf("-----------map----------\n");
	debug_intmap(data.map);
	printf("----------init----------\n");
	printf("posX  =  %f\n", data.posY);
	printf("posY  =  %f\n", data.posY);
	printf("dirX  =  %f\n", data.v_dirX);
	printf("dirY  =  %f\n", data.v_dirY);
	printf("plaX  =  %f\n", data.v_planeX);
	printf("plaY  =  %f\n", data.v_planeY);
}

int	window_close(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

int main(int argc, char **argv) {
	t_data	data;

	data = analyze_cub(argv[1]);
	data.mlx = mlx_init();
	//! MAKEFILE WILDCARD使用中
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


	//!小松のposxがinitできてない？
	//!自分のところをしっかり０にしてある？
	printall(data);
	printf("last = %d\n", data.map[12][27]);
	data.posX = 27.0;
	// data.map[12][27] = 0;
	printf("last = %d\n", data.map[12][27]);
	printf("pos = %f\n", data.posX);
	//!
	
	mlx_loop_hook(data.mlx, &mainloop, &data);
	mlx_hook(data.win, KEY_PRESS, 0, &key_press, &data);
	mlx_hook(data.win, KEY_RELEASE, 0, &key_release, &data);
	mlx_hook(data.win, ON_DESTROY, 0, &window_close, &data);
	mlx_loop(data.mlx);
}
