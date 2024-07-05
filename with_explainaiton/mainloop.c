/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:03:42 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/06 07:41:13 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void	updata_key_ad(t_data *data)
{
	double	tmpX;
	double	tmpY;
	int		rotSpeed;

	if (data->key_a == GO)
		rotSpeed = data->rotSpeed;
	else if (data->key_d == GO)
		rotSpeed = data->rotSpeed * (-1);
	else
		return (0);
	tmpX = data->v_dirX;
	tmpY = data->v_dirY;
	// rotate fomula. read the math textbook if you don't understand ;(
	data->v_dirX = tmpX * cos(rotSpeed) - tmpY * sin(rotSpeed);
	data->v_dirY = tmpX * sin(rotSpeed) + tmpY * cos(rotSpeed);
	tmpX = data->v_planeX;
	tmpY = data->v_planeY;
	data->v_planeX = tmpX * cos(rotSpeed) - tmpY * sin(rotSpeed);
	data->v_planeY = tmpX * sin(rotSpeed) + tmpY * cos(rotSpeed);
}

static void	update_key_ws(t_data *data)
{
	if (data->key_w)
	{
		//wall collision check and move forward!
		if (data->map[(int)(data->posX + data->v_dirX * data->moveSpeed)]\
					[(int)(data->posY)])
			data->posX += data->v_dirX * data->moveSpeed;
		if (data->map[(int)(data->posX)]\
					[(int)(data->posY + data->v_dirY * data->moveSpeed)])
			data->posY += data->v_dirY * data->moveSpeed;
	}
	if (data->key_s)
	{
		//wall collision check and move backward!
		if (data->map[(int)(data->posX - data->v_dirX * data->moveSpeed)]\
					[(int)(data->posY)])
			data->posX -= data->v_dirX * data->moveSpeed;
		if (data->map[(int)(data->posX)]\
					[(int)(data->posY - data->v_dirY * data->moveSpeed)])
			data->posY -= data->v_dirY * data->moveSpeed;
	}
}

int	mainloop(t_data *data)
{
	int	x;
	int	y;

	//!overflow
	//*raycast to floor, ceiling. store color data into buf.
	//*raycast to walls. update the buf.
	//*output buf. update player's position.

	floor_ceiling_casting(data);
	wall_casting(data);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++y < WIDTH)
		data->img.info[y * WIDTH + x] = data->buf[y][x];
	}
	//finally, put color on the screen :))))))
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	//update your location!
	update_key_ws(data);
	updata_key_ad(data);
	return (0);
}
