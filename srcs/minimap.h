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
	int	mapX;
	int	mapY;
	int	c_x;
	int	c_y;
} t_mini;

void	minimap_casting(t_data *data);

#endif
