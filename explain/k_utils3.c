/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_utils3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 10:51:45 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/07/06 10:13:36 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	get_now_width(int **map, int height)
{
	int	width;

	width = 0;
	while (map[height][width] != -1)
		width++;
	return (width);
}

int	get_now_height(int **map, int width)
{
	int	height;

	height = 0;
	while (map[height][width] != -1)
		height++;
	return (height);
}

int	get_max_width_intpp(int **map)
{
	int	i;
	int	max;
	int	stk;

	i = 0;
	max = 0;
	stk = 0;
	while (map[i])
	{
		stk = ft_intplen(map[i]);
		if (max < stk)
			max = stk;
		i++;
	}
	return (max);
}

int	get_max_width_charpp(char **map)
{
	int	i;
	int	max;
	int	stk;

	i = 0;
	max = 0;
	stk = 0;
	while (map[i])
	{
		stk = ft_strlen(map[i]);
		if (max < stk)
			max = stk;
		i++;
	}
	return (max);
}

int	*make_off_line(int width, int num)
{
	int	*line;
	int	i;

	line = (int *)malloc(sizeof(int) * (width + 2));
	i = 0;
	while (i < width + 1)
	{
		line[i] = num;
		i++;
	}
	line[i] = -1;
	return (line);
}
