/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:49:47 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/03 18:50:41 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static void	get_image(t_data *data, int *texture, char *path, t_img *img)
{
	int x;
	int y;

	img->img = mlx_xpm_file_to_image(data->mlx, path, &img->img_width, &img->img_height);
	img->info = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);;
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		//二次元の画像データを１次元に変換して格納
		while (++y < img->img_width)
			texture[img->img_width * y + x] = img->info[img->img_width * y + x];
	}
	mlx_destroy_image(data->mlx, img->img);
	//データの解放
}

static void	install_image(t_data *data)
{
	t_img	img;

	get_img(data, data->texture[0], WALLEAST, &img);
	get_img(data, data->texture[1], WALLWEST, &img);
	get_img(data, data->texture[2], WALLNORTH, &img);
	get_img(data, data->texture[3], WALLSOUTH, &img);
	get_img(data, data->texture[4], CEILING, &img);
	get_img(data, data->texture[5], FLOOR, &img);
}

static int	allocate_texture(void)
{
	int i;
	int	**res;

	res = (int **)malloc(sizeof(int *) * TEXTURE_NUM);
	if (res == NULL)
		return (NULL);
	i = -1;
	while (++i < TEXTURE_NUM)
	{
		res[i] = (int *)malloc(sizeof(int) * (BLOCKHEIGHT * BLOCKWIDTH));
		if (res == NULL)
			break ;
	}
	if (res[i] == NULL)
	{
		while (--i >= 0)
			free(res[i]);
		return (free(res), NULL);
	}
	return (res);
}

int	init_data(t_data *data)
{
	int	h;
	int	w;

	data->mlx = mlx_init();
	//posX, Y, 等はマップ解析で入れるから、ここじゃなくてもいいかも
	h = -1;
	while (++h < HEIGHT)
	{
		w = -1;
		while (++w < WIDTH)
			data->buf[h][w] = 0;
	}
	data->texture = allocate_texture();
	if (data->texture == NULL)
		return (MALLOCERROR);
	h = -1;
	while (++h < BLOCKHEIGHT)
	{
		w = -1;
		while (++w < BLOCKWIDTH)
			data->texture[h][w] = 0;
	}
	install_image(data);
	return (OK);
}
