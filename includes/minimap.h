/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:50:41 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/08 13:51:02 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "all.h"

# define MINI_H 192
# define MINI_W 192
# define MINI_BLOCK 3

# define BLACK 0
# define RED 0xFF0000
# define GREY 0xCCCCCC
# define GREEN 0x00FF00

typedef struct s_mini
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;
	int	c_x;
	int	c_y;
}	t_mini;

void	minimap_casting(t_data *data);

#endif
