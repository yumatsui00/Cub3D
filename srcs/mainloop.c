/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:03:42 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/08 13:57:07 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void	update_key_ad(t_data *data)
{
	double	tmp_x;
	double	tmp_y;
	double	rot_speed;

	if (data->key_a == GO)
		rot_speed = data->rotSpeed * (-1);
	else if (data->key_d == GO)
		rot_speed = data->rotSpeed;
	else
		return ;
	tmp_x = data->v_dirX;
	tmp_y = data->v_dirY;
	data->v_dirX = tmp_x * cos(rot_speed) - tmp_y * sin(rot_speed);
	data->v_dirY = tmp_x * sin(rot_speed) + tmp_y * cos(rot_speed);
	tmp_x = data->v_planeX;
	tmp_y = data->v_planeY;
	data->v_planeX = tmp_x * cos(rot_speed) - tmp_y * sin(rot_speed);
	data->v_planeY = tmp_x * sin(rot_speed) + tmp_y * cos(rot_speed);
}

static void	update_key_ws(t_data *data)
{
	if (data->key_w)
	{
		if (!data->map[(int)(data->posY)] \
			[(int)(data->posX + data->v_dirX * data->moveSpeed * data->dash)])
			data->posX += data->v_dirX * data->moveSpeed * data->dash;
		if (!data->map[(int)(data->posY + data->v_dirY * \
			data->moveSpeed * data->dash)][(int)(data->posX)])
			data->posY += data->v_dirY * data->moveSpeed * data->dash;
	}
	if (data->key_s)
	{
		if (!data->map[(int)(data->posY)]\
					[(int)(data->posX - data->v_dirX * \
						data->moveSpeed * data->dash)])
			data->posX -= data->v_dirX * data->moveSpeed * data->dash;
		if (!data->map[(int)(data->posY - data->v_dirY *\
						data->moveSpeed * data->dash)][(int)(data->posX)])
			data->posY -= data->v_dirY * data->moveSpeed * data->dash;
	}
}

int	mainloop(t_data *data)
{
	int	x;
	int	y;

	update_key_ws(data);
	update_key_ad(data);
	floor_ceiling_casting(data);
	wall_casting(data);
	if (data->mini % 2 == 1)
		minimap_casting(data);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			data->img.info[y * WIDTH + x] = data->buf[y][x];
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
