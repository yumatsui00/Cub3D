/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:24:55 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/07/07 14:51:17 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include "libft/libft.h"

// #include <libc.h>
// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }

static int	check_filename(char *filename)
{
	int		i;
	int		len;
	char	*last_4_string;
	int		flag;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	i = len - 4;
	last_4_string = ft_substr(filename, i, 4);
	if (!last_4_string)
		(write(1, "Error\n", 6), exit(0));
	if (last_4_string && !ft_strncmp(last_4_string, ".cub", 4))
		flag = 1;
	else
		flag = 0;
	free(last_4_string);
	return (flag);
}

static t_analyze	*init_texture(void)
{
	t_analyze	*ret;

	ret = (t_analyze *)malloc(sizeof(t_analyze));
	ret->n_texture_path = NULL;
	ret->s_texture_path = NULL;
	ret->e_texture_path = NULL;
	ret->w_texture_path = NULL;
	ret->f_rgb.r = -1;
	ret->f_rgb.g = -1;
	ret->f_rgb.b = -1;
	ret->c_rgb.r = -1;
	ret->c_rgb.g = -1;
	ret->c_rgb.b = -1;
	return (ret);
}

static void	k_init_item1(t_data *ret, t_analyze *component, t_position *pos)
{
	ret->map = component->map;
	ret->posX = pos->x;
	ret->posY = pos->y;
	ret->n_texture_path = component->n_texture_path;
	ret->s_texture_path = component->s_texture_path;
	ret->w_texture_path = component->w_texture_path;
	ret->e_texture_path = component->e_texture_path;
	ret->n_texture_path[ft_strlen(ret->n_texture_path) - 1] = '\0';
	ret->s_texture_path[ft_strlen(ret->s_texture_path) - 1] = '\0';
	ret->w_texture_path[ft_strlen(ret->w_texture_path) - 1] = '\0';
	ret->e_texture_path[ft_strlen(ret->e_texture_path) - 1] = '\0';
	ret->f_rgb = component->f_rgb;
	ret->c_rgb = component->c_rgb;
}

t_data	k_init(t_analyze *component, t_position pos)
{
	t_data	ret;
	int		minus_flag;

	k_init_item1(&ret, component, &pos);
	if (pos.direction == NORTH || pos.direction == WEST)
		minus_flag = -1;
	else
		minus_flag = 1;
	if (pos.direction == NORTH || pos.direction == SOUTH)
	{
		ret.v_dirX = 0;
		ret.v_dirY = minus_flag;
		ret.v_planeX = ret.v_dirY * SCALE * minus_flag;
		ret.v_planeY = 0;
	}
	else
	{
		ret.v_dirX = minus_flag;
		ret.v_dirY = 0;
		ret.v_planeX = 0;
		ret.v_planeY = ret.v_dirX * SCALE * minus_flag;
	}
	return (ret);
}

t_data	analyze_cub(char *filepath)
{
	t_analyze	*component;
	t_data		data;
	t_position	pos;

	if (!check_filename(filepath))
		(write(1, "Error\n", 6), exit(0));
	component = init_texture();
	pos = assignment_all(component, filepath);
	if (!pos.direction)
		(write(1, "Error\n", 6), exit(0));
	return (k_init(component, pos));
}

// int	main(int ac, char **av)
// {
// 	t_data a;

// 	a = analyze_cub(av[1]);
// 	// if (a)
// 	// {
// 	// 	printf("%s\n", a->n_texture_path);
// 	// 	printf("%s\n", a->s_texture_path);
// 	// 	printf("%s\n", a->w_texture_path);
// 	// 	printf("%s\n", a->e_texture_path);
// 	// 	printf("%d %d %d\n", a->f_rgb.r, a->f_rgb.g, a->f_rgb.b);
// 	// 	printf("%d %d %d\n", a->c_rgb.r, a->c_rgb.g, a->c_rgb.b);
// 	// }
// }