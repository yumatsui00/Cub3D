/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:52:42 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/07 20:34:51 by yumatsui         ###   ########.fr       */
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
//視野角定数
# define SCALE 0.66
//壁紙の名前 最低6 多分
# define TEXTURE_NUM 6
# define CEILING "pic.xpm"
# define FLOOR "pic.xpm"
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
	double	posX;
	double	posY;
	double	v_dirX;
	double	v_dirY;
	double	v_planeX;
	double	v_planeY;
	char	*n_texture_path;
	char	*s_texture_path;
	char	*e_texture_path;
	char	*w_texture_path;
	t_rgb	f_rgb;
	t_rgb	c_rgb;
	void *mlx; //初期化済
	void *win; //済
	//以下初期化なし
	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_esc;
	double		dash;
	t_img	img;
	int buf[HEIGHT][WIDTH]; //初期化済
	double	zBuffer[WIDTH];
	int **texture;    //初期化済
	double moveSpeed; //すみ
	double rotSpeed;  //済み
	int	mini;
}			t_data;

#endif