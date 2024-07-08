/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:30:32 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/08 13:45:07 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "all.h"

typedef struct s_mypov_for_floor
{
	int		x;
	int		y;
	float	relative_y;
	float	pos_z;
	float	row_distance;
}	t_mypov4floor;

typedef struct s_godpov_for_floor
{
	float	v_ray_xl;
	float	v_ray_xr;
	float	v_ray_yl;
	float	v_ray_yr;
	float	v_step_x;
	float	v_step_y;
	float	floor_x;
	float	floor_y;
}	t_godpov4floor;

typedef struct s_mypov_for_wall
{
	int		x;
	int		y;
	double	cam_x;
	int		wallheight;
	int		wall_u_edge;
	int		wall_l_edge;
}	t_mypov4wall;

typedef struct s_godpov_for_wall
{
	double	v_ray_x;
	double	v_ray_y;
	int		map_x;
	int		map_y;
	double	cell_dist_x;
	double	cell_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		ns_flag;
	double	holiz_dist;
}	t_godpov4wall;

typedef struct s_tx
{
	double	wall_x;
	int		x;
	int		y;
	double	step;
	double	start;
	int		color;
	int		num;
}	t_tx;

#endif