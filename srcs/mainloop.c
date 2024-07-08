/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:03:42 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/08 19:55:48 by yumatsui         ###   ########.fr       */
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

static void	update_key_ws(t_data *d)
{
	if (d->key_w)
	{
		if (!d->map[(int)(d->posY + 0.05)][(int)(d->posX + d->v_dirX * \
		d->moveSpeed * d->dash + 0.05)] && !d->map[(int)(d->posY - 0.05)]
		[(int)(d->posX + d->v_dirX * d->moveSpeed * d->dash - 0.05)])
			d->posX += d->v_dirX * d->moveSpeed * d->dash;
		if (!d->map[(int)(d->posY + d->v_dirY * d->moveSpeed * d->dash + 0.05)] \
		[(int)(d->posX + 0.05)] && !d->map[(int)(d->posY + d->v_dirY * \
		d->moveSpeed * d->dash - 0.05)][(int)(d->posX - 0.05)])
			d->posY += d->v_dirY * d->moveSpeed * d->dash;
	}
	if (d->key_s)
	{
		if (!d->map[(int)(d->posY + 0.05)][(int)(d->posX - d->v_dirX * \
		d->moveSpeed * d->dash + 0.05)] && !d->map[(int)(d->posY - 0.05)] \
		[(int)(d->posX - d->v_dirX * d->moveSpeed * d->dash - 0.05)])
			d->posX -= d->v_dirX * d->moveSpeed * d->dash;
		if (!d->map[(int)(d->posY - d->v_dirY * d->moveSpeed * d->dash + 0.05)] \
		[(int)(d->posX + 0.05)] && !d->map[(int)(d->posY - \
		d->v_dirY * d->moveSpeed * d->dash - 0.05)][(int)(d->posX - 0.05)])
			d->posY -= d->v_dirY * d->moveSpeed * d->dash;
	}
}

int	mainloop(t_data *data)
{
	int	x;
	int	y;
	int	i = 0;

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
