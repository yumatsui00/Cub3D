#ifndef RAYCAST_H
# define RAYCAST_H

# include "all.h"

//カメラ視点でのx, y座標
typedef struct s_mypov_for_floor
{
	//floor変数
	int		x;
	int		y;
	float	rayXL;
	float	rayXR;
	float	rayYL;
	float	rayYR;
	float	relative_y;
	float	posZ;
	float	rowDistance;
} t_mypov_for_floor;

//マップを上から見た際のx, y座標
typedef struct s_godpov_for_floor
{
	//floor  変数
	float	stepX;
	float	stepY;
	float	floorX;
	float	floorY;
	int		mapX;
	int		mapY;
} t_godpov_for_floor;


#endif