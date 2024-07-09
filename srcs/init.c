/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:49:47 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/09 16:20:11 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

static void	get_img2(t_data *data, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->img = mlx_xpm_file_to_image(data->mlx, \
				path, &img->img_width, &img->img_height);
	if (img->img == NULL)
		return ;
	img->info = (int *)mlx_get_data_addr(img->img, \
				&img->bpp, &img->size_l, &img->endian);
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
			texture[img->img_width * y + x] = img->info[img->img_width * y + x];
	}
	mlx_destroy_image(data->mlx, img->img);
}

static int	get_img(t_data *data, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;
	int	fd;

	fd = open (path, O_RDONLY);
	if (fd < 0)
		exit(write(2, "Error\n", 6));
	img->img = mlx_xpm_file_to_image(data->mlx, \
				path, &img->img_width, &img->img_height);
	if (img->img == NULL)
		exit(write(2, "Error\n", 6));
	img->info = (int *)mlx_get_data_addr(img->img, \
				&img->bpp, &img->size_l, &img->endian);
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
			texture[img->img_width * y + x] = img->info[img->img_width * y + x];
	}
	mlx_destroy_image(data->mlx, img->img);
	return (close(fd));
}

static void	install_image(t_data *data)
{
	t_img	img;

	get_img(data, data->texture[WALLEAST_NUM], data->e_texture_path, &img);
	get_img(data, data->texture[WALLWEST_NUM], data->w_texture_path, &img);
	get_img(data, data->texture[WALLNORTH_NUM], data->n_texture_path, &img);
	get_img(data, data->texture[WALLSOUTH_NUM], data->s_texture_path, &img);
	get_img2(data, data->texture[CEILING_NUM], CEILING, &img);
	get_img2(data, data->texture[FLOOR_NUM], FLOOR, &img);
}

static int	**allocate_texture(void)
{
	int	i;
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
	return (res);
}

int	init_data(t_data *data)
{
	int	h;
	int	w;

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
	while (++h < TEXTURE_NUM)
	{
		w = -1;
		while (++w < BLOCKHEIGHT * BLOCKWIDTH)
			data->texture[h][w] = 0;
	}
	install_image(data);
	data->move_speed = MOVESPEED;
	data->rot_speed = ROTSPEED;
	return (OK);
}
