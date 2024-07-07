/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_analyze_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:37:31 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/07/07 14:25:14 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_position	get_position(int **map)
{
	t_position	ret;
	int			x;
	int			y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != -1)
		{
			if (map[y][x] == NORTH || map[y][x] == SOUTH || map[y][x] == WEST
				|| map[y][x] == EAST)
			{
				ret.x = x;
				ret.y = y;
				ret.direction = map[y][x];
			}
			x++;
		}
		y++;
	}
	return (ret);
}

void	init_dx_dy(int dx[4], int dy[4])
{
	dx[0] = 0;
	dx[1] = 0;
	dx[2] = -1;
	dx[3] = 1;
	dy[0] = -1;
	dy[1] = 1;
	dy[2] = 0;
	dy[3] = 0;
}

int	**init_visited(int **map)
{
	int	i;
	int	j;
	int	**visited;
	int	size;
	int	len;

	i = 0;
	size = ft_intpplen(map);
	visited = (int **)malloc(sizeof(int *) * (size + 1));
	len = get_max_width_intpp(map);
	while (i < size + 1)
	{
		j = 0;
		visited[i] = (int *)malloc(sizeof(int) * len);
		while (j < len)
		{
			visited[i][j] = 0;
			j++;
		}
		i++;
	}
	visited[i] = NULL;
	return (visited);
}

int	solvemap(int **map, int x, int y, int **visited)
{
	int	dx[4];
	int	dy[4];
	int	newX;
	int	newY;
	int	i;
	int	cols;
	int	rows;

	init_dx_dy(dx, dy);
	cols = get_max_width_intpp(map) + 1;
	rows = ft_intpplen(map) + 1;
	if (x < 0 || x >= cols || y < 0 || y >= rows || map[y][x] == 1
		|| map[y][x] == 9 || visited[y][x])
		return (0);
	if ((x > 0 && map[y][x - 1] == 9) || (x < cols - 1 && map[y][x + 1] == 9)
		|| (y > 0 && map[y - 1][x] == 9) || (y < rows - 1 && map[y
			+ 1][x] == 9))
		return (1);
	visited[y][x] = 1;
	i = 0;
	while (i < 4)
	{
		newX = x + dx[i];
		newY = y + dy[i];
		if (solvemap(map, newX, newY, visited))
			return (1);
		i++;
	}
	return (0);
}

t_position	analyze_map(int **map)
{
	t_position	position;
	int			flag;
	int			**visited;

	position = get_position(map);
	visited = init_visited(map);
	flag = solvemap(map, position.x, position.y, visited);
	free(visited);
	if (!flag)
		return (position);
	position.direction = 0;
	return (position);
}
