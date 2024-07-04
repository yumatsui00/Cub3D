/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:52:42 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/04 12:11:19 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

//!初期値
# define WIDTH 640
# define HEIGHT 480
# define MOVESPEED 0.05
# define ROTSPEED 0.05
//視野角定数
# define SCALE 0.66
//壁紙の名前 最低6 多分
# define TEXTURE_NUM 6
# define WALLEAST "texture/blabla"
# define WALLWEST
# define WALLNORTH
# define WALLSOUTH
# define CEILING
# define FLOOR
//壁紙のピクセル数
# define BLOCKHEIGHT 64 //仮
# define BLOCKWIDTH 64

typedef struct	s_img
{
	void	*img;
	int		*info;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

//この辺はマップ解析とともに入力してく　
typedef struct s_data
{
	int		**map;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	void	*mlx; //初期化済
	void	*win; //済
	//以下初期化なし
	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_esc;
	t_img	img;
	int		buf[HEIGHT][WIDTH]; //初期化済
	double	zBuffer[WIDTH];
	int		**texture; //初期化済
	double	moveSpeed;//すみ
	double	rotSpeed;//済み
}	t_data;

typedef struct s_cal
{
	int		x;
	int		y;
	float	rayDirXLeft;
	float	rayDirXRight;
	float	rayDirYLeft;
	float	rayDirYRight;
	int		currenty;
	float	posZ;
	float	rowDistance;
	float	floorStepX;
	float	floorStepY;

	float	floorX;
	float	floorY;
	int		cellX;
	int		cellY;
	int		tx;
	int		ty;
}	t_cal;

#endif