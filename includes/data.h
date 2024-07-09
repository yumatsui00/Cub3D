/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:52:42 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/09 14:08:28 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

#include "all.h"


# define ON_DESTROY 17
//!初期値
# define WIDTH 640
# define HEIGHT 480
# define MOVESPEED 0.05
# define ROTSPEED 0.05
# define DASH 2.0
# define MOUSEROT 0.005
//視野角定数
# define SCALE 0.66
//壁紙の名前 最低6 多分
# define TEXTURE_NUM 6
# define CEILING "texture/ice.xpm"
# define FLOOR "texture/walkstone.xpm"
# define WALLEAST_NUM 0
# define WALLWEST_NUM 1
# define WALLNORTH_NUM 2
# define WALLSOUTH_NUM 3
# define CEILING_NUM 4
# define FLOOR_NUM 5
//壁紙のピクセル数
# define BLOCKHEIGHT 64 //仮
# define BLOCKWIDTH 64

struct		s_rgb
{
	int		r;
	int		g;
	int		b;
} typedef t_rgb;

struct		s_position
{
	int		x;
	int		y;
	int		direction;
} typedef t_position;

struct		s_analyze
{
	char	*n_texture_path;
	char	*s_texture_path;
	char	*e_texture_path;
	char	*w_texture_path;
	char	*f_texture_path;
	char	*c_texture_path;
	int		direction;
	t_rgb	f_rgb;
	t_rgb	c_rgb;
	int		**map;
} typedef t_analyze;


typedef struct s_img
{
	void	*img;
	int		*info;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}			t_img;

//この辺はマップ解析とともに入力してく　
typedef struct s_data
{
	int		**map;
	double	pos_x;
	double	pos_y;
	double	v_dir_x;
	double	v_dir_y;
	double	v_plane_x;
	double	v_plane_y;
	char	*n_texture_path;
	char	*s_texture_path;
	char	*e_texture_path;
	char	*w_texture_path;
	t_rgb	f_rgb;
	t_rgb	c_rgb;
	void 	*mlx;
	void 	*win;
	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_esc;
	double	dash;
	t_img	img;
	int 	buf[HEIGHT][WIDTH];
	int 	**texture;
	double	moveSpeed;
	double	rotSpeed;
	int		mini;
	int		mouse;
}			t_data;

typedef struct s_ms
{
	int		dx;
	int		dy;
	double	tmpx;
	double	tmpy;
}	t_ms;

#endif