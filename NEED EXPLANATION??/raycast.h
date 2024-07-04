#ifndef RAYCAST_H
# define RAYCAST_H

# include "all.h"

//座標または通常のスカラー値は特に表記無し
//ベクトルの値は値は頭にv_
//カメラ視点でのx, y座標
typedef struct s_mypov_for_floor
{
	//floor変数
	int		x;
	int		y;
	float	relative_y;
	float	posZ;
	float	rowDistance;
} t_mypov4floor;

//マップを上から見た際のx, y座標
typedef struct s_godpov_for_floor
{
	float	v_rayXL;
	float	v_rayXR;
	float	v_rayYL;
	float	v_rayYR;
	float	v_stepX;
	float	v_stepY;
	float	floorX;
	float	floorY;
	int		mapX;
	int		mapY;
} t_godpov4floor;

typedef struct s_mypov_for_wall
{
	int	x;
	int	y;
	double	camX;
	int	wallheight;
	int	wallUpperEdge;
	int	wallLowerEdge;
} t_mypov4wall;

typedef struct s_godpov_for_wall
{
	double	v_rayX;
	double	v_rayY;
	int	mapX;
	int	mapY;
	double cellDistX;
	double cellDistY;
	double sideDistX;
	double sideDistY;
	int	stepX;
	int	stepY;
	int		NorthSouthFlag;
	double	holizDist;
} t_godpov4wall;

#endif