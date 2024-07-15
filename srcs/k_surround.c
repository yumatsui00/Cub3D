/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_surround.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:48:36 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/07/15 15:48:42 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

static int	component1(int **map, int x, int y)
{
	int	count;

	count = 0;
	if (map[y - 1][x - 1] == 9 || map[y - 1][x - 1] == -1)
		count++;
	if (map[y - 1][x] == 9 || map[y - 1][x] == -1)
		count++;
	if (map[y - 1][x + 1] == 9 || map[y - 1][x + 1] == -1)
		count++;
	if (map[y][x - 1] == 9 || map[y][x - 1] == -1)
		count++;
	if (map[y][x + 1] == 9 || map[y][x + 1] == -1)
		count++;
	if (map[y + 1][x - 1] == 9 || map[y + 1][x - 1] == -1)
		count++;
	if (map[y + 1][x] == 9 || map[y + 1][x] == -1)
		count++;
	if (map[y + 1][x + 1] == 9 || map[y + 1][x + 1] == -1)
		count++;
	if (count == 8)
		return (0);
	return (1);
}

static int	component0(int **map, int x, int y)
{
	if (map[y - 1][x] == 9 || map[y - 1][x] == -1)
		return (0);
	if (map[y][x - 1] == 9 || map[y][x - 1] == -1)
		return (0);
	if (map[y][x + 1] == 9 || map[y][x + 1] == -1)
		return (0);
	if (map[y + 1][x] == 9 || map[y + 1][x] == -1)
		return (0);
	return (1);
}

// It's no good if 0 touches 9 and -1
int	check_surround(int **map)
{
	int	x;
	int	y;

	y = 1;
	while (map[y])
	{
		x = 1;
		while (map[y][x] != -1)
		{
			if (map[y][x] == 0)
				if (!component0(map, x, y))
					return (0);
			if (map[y][x] == 1)
				if (!component1(map, x, y))
					return (0);
			x++;
		}
		y++;
	}
	return (1);
}
