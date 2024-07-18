/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:03:42 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/19 01:39:31 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

static void	update_key_ad(t_data *d)
{
	if (d->key_d)
	{
		if (!d->map[(int)(d->pos_y + 0.05)][(int)(d->pos_x + d->v_plane_x * \
		d->move_speed * d->dash + 0.05)] && !d->map[(int)(d->pos_y - 0.05)]
		[(int)(d->pos_x + d->v_plane_x * d->move_speed * d->dash - 0.05)])
			d->pos_x += d->v_plane_x * d->move_speed * d->dash;
		if (!d->map[(int)(d->pos_y + d->v_plane_y * d->move_speed * d->dash + \
		0.05)][(int)(d->pos_x + 0.05)] && !d->map[(int)(d->pos_y + \
		d->v_plane_y * d->move_speed * d->dash - 0.05)][(int)(d->pos_x - 0.05)])
			d->pos_y += d->v_plane_y * d->move_speed * d->dash;
	}
	if (d->key_a)
	{
		if (!d->map[(int)(d->pos_y + 0.05)][(int)(d->pos_x - d->v_plane_x * \
		d->move_speed * d->dash + 0.05)] && !d->map[(int)(d->pos_y - 0.05)] \
		[(int)(d->pos_x - d->v_plane_x * d->move_speed * d->dash - 0.05)])
			d->pos_x -= d->v_plane_x * d->move_speed * d->dash;
		if (!d->map[(int)(d->pos_y - d->v_plane_y * d->move_speed * d->dash \
		+ 0.05)][(int)(d->pos_x + 0.05)] && !d->map[(int)(d->pos_y - \
		d->v_plane_y * d->move_speed * d->dash - 0.05)][(int)(d->pos_x - 0.05)])
			d->pos_y -= d->v_plane_y * d->move_speed * d->dash;
	}
}

static void	update_key_ws(t_data *d)
{
	if (d->key_w)
	{
		if (!d->map[(int)(d->pos_y + 0.05)][(int)(d->pos_x + d->v_dir_x * \
		d->move_speed * d->dash + 0.05)] && !d->map[(int)(d->pos_y - 0.05)]
		[(int)(d->pos_x + d->v_dir_x * d->move_speed * d->dash - 0.05)])
			d->pos_x += d->v_dir_x * d->move_speed * d->dash;
		if (!d->map[(int)(d->pos_y + d->v_dir_y * d->move_speed * d->dash + \
		0.05)][(int)(d->pos_x + 0.05)] && !d->map[(int)(d->pos_y + \
		d->v_dir_y * d->move_speed * d->dash - 0.05)][(int)(d->pos_x - 0.05)])
			d->pos_y += d->v_dir_y * d->move_speed * d->dash;
	}
	if (d->key_s)
	{
		if (!d->map[(int)(d->pos_y + 0.05)][(int)(d->pos_x - d->v_dir_x * \
		d->move_speed * d->dash + 0.05)] && !d->map[(int)(d->pos_y - 0.05)] \
		[(int)(d->pos_x - d->v_dir_x * d->move_speed * d->dash - 0.05)])
			d->pos_x -= d->v_dir_x * d->move_speed * d->dash;
		if (!d->map[(int)(d->pos_y - d->v_dir_y * d->move_speed * d->dash \
		+ 0.05)][(int)(d->pos_x + 0.05)] && !d->map[(int)(d->pos_y - \
		d->v_dir_y * d->move_speed * d->dash - 0.05)][(int)(d->pos_x - 0.05)])
			d->pos_y -= d->v_dir_y * d->move_speed * d->dash;
	}
}

static void	update_key_arrow(t_data *data)
{
	double	tmp_x;
	double	tmp_y;
	double	rot_speed;

	if (data->key_left == GO)
		rot_speed = data->rot_speed * (-1);
	else if (data->key_right == GO)
		rot_speed = data->rot_speed;
	else
		return ;
	tmp_x = data->v_dir_x;
	tmp_y = data->v_dir_y;
	data->v_dir_x = tmp_x * cos(rot_speed) - tmp_y * sin(rot_speed);
	data->v_dir_y = tmp_x * sin(rot_speed) + tmp_y * cos(rot_speed);
	tmp_x = data->v_plane_x;
	tmp_y = data->v_plane_y;
	data->v_plane_x = tmp_x * cos(rot_speed) - tmp_y * sin(rot_speed);
	data->v_plane_y = tmp_x * sin(rot_speed) + tmp_y * cos(rot_speed);
}

int	mainloop(t_data *data)
{
	int	x;
	int	y;

	update_key_ws(data);
	update_key_arrow(data);
	update_key_ad(data);
	floor_ceiling_casting(data);
	wall_casting(data);
	if (data->mini)
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
