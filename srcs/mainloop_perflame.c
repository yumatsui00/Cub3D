/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainloop_perflame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:03:42 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/05 17:14:00 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	calculate(t_data *data)
{
	floor_ceiling_casting(data);
	wall_casting(data);
}

int	mainloop_perflame(t_data *data)
{
	int	x;
	int	y;

	calculate(data);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++y < WIDTH)
		data->img.info[y * WIDTH + x] = data->buf[y][x];
	}
	key_update(data);
	return (0);
}