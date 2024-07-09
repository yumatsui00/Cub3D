/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:04:31 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/09 15:30:48 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

int	window_close(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}

int	mouse_move(int x, int y, t_data *data)
{
	static int	last_x;
	static int	last_y;
	t_ms		ms;

	// check on/off
	if (data->mouse % 2 == 0)
		return (0);
	// check which direction the mouse moved, and rotate
	ms.dx = x - last_x;
	ms.dy = y - last_y;
	ms.tmpx = data->v_dir_x;
	ms.tmpy = data->v_dir_y;
	// rotate fomula. read math textbook if you dont understand!
	data->v_dir_x = ms.tmpx * cos(ms.dx * MOUSEROT) - ms.tmpy * sin(ms.dx
			* MOUSEROT);
	data->v_dir_y = ms.tmpx * sin(ms.dx * MOUSEROT) + ms.tmpy * cos(ms.dx
			* MOUSEROT);
	ms.tmpx = data->v_plane_x;
	ms.tmpy = data->v_plane_y;
	data->v_plane_x = ms.tmpx * cos(ms.dx * MOUSEROT) - ms.tmpy * sin(ms.dx
			* MOUSEROT);
	data->v_plane_y = ms.tmpx * sin(ms.dx * MOUSEROT) + ms.tmpy * cos(ms.dx
			* MOUSEROT);
	//update for next time
	last_x = x;
	last_y = y;
	return (0);
}

static void	init(t_data *data, int argc)
{
	//init
	argc = 0;//-Wall -Wextra -Werror ;(
	data->key_a = 0;
	data->key_w = 0;
	data->key_s = 0;
	data->key_d = 0;
	data->key_esc = 0;
	//make camerea on the center of a block
	data->pos_x += 0.5;
	data->pos_y += 0.5;
	//init
	data->dash = 1;
	data->mini = 0;
	data->mouse = 0;
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.info = (int *)mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.size_l, &data->img.endian);
	if (data->v_dir_x == -1)
		data->v_plane_y *= -1;
	if (data->v_dir_y == 1)
		data->v_plane_x *= -1;
}

int	main(int argc, char **argv)
{
	t_data	data;

	data = analyze_cub(argv[1]);
	data.mlx = mlx_init();
	if (init_data(&data) == MALLOCERROR)
		return (MALLOCERROR);
	init(&data, argc);
	mlx_loop_hook(data.mlx, &mainloop, &data);
	mlx_hook(data.win, KEY_PRESS, 0, &key_press, &data);
	mlx_hook(data.win, KEY_RELEASE, 0, &key_release, &data);
	mlx_hook(data.win, 6, 0, &mouse_move, &data);
	mlx_hook(data.win, ON_DESTROY, 0, &window_close, &data);
	mlx_loop(data.mlx);
}

// #include <libc.h>
// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }