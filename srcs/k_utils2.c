/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:20:44 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/07/05 10:07:56 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	ft_intplen(int *line)
{
	int	len;

	len = 0;
	while (line[len] != -1)
		len++;
	return (len);
}

int	ft_intpplen(int **map)
{
	int	len;

	len = 0;
	while (map[len])
		len++;
	return (len);
}

int	**ft_intppjoin(int **map, int *row)
{
	int	i;
	int	**next_map;

	i = 0;
	if (!map)
	{
		next_map = (int **)malloc(sizeof(int *) * 2);
		if (!next_map)
			return (NULL);
		next_map[0] = row;
		next_map[1] = NULL;
		return (next_map);
	}
	next_map = (int **)malloc(sizeof(int *) * (ft_intpplen(map) + 2));
	if (!next_map)
		return (free_double_ptr_int(map), NULL);
	while (map[i])
	{
		next_map[i] = map[i];
		i++;
	}
	next_map[i] = row;
	next_map[i + 1] = NULL;
	// free_double_ptr_int(map);
	return (next_map);
}

int	ft_strpplen(char **map)
{
	int	len;

	len = 0;
	while (map[len])
		len++;
	return (len);
}

char	**ft_strppjoin(char **map, char *row)
{
	int i;
	char **next_map;

	if (!map)
	{
		next_map = (char **)malloc(sizeof(char *) * 2);
		if (!next_map)
			return (NULL);
		next_map[0] = ft_strdup(row);
		next_map[1] = NULL;
		return (next_map);
	}
	i = 0;
	next_map = (char **)malloc(sizeof(char *) * (ft_strpplen(map) + 2));
	if (!next_map)
		return (free_double_ptr(map), NULL);
	while (map[i])
	{
		next_map[i] = ft_strdup(map[i]);
		i++;
	}
	next_map[i] = ft_strdup(row);
	next_map[i + 1] = NULL;
	free_double_ptr(map);
	return (next_map);
}