/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:53:47 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/07/06 17:57:27 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	free_double_ptr(char **s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
		i++;
	j = 0;
	while (j < i)
	{
		free(s[j]);
		j++;
	}
	free(s);
}

void	free_double_ptr_int(int **s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
		i++;
	j = 0;
	while (j < i)
	{
		free(s[j]);
		j++;
	}
	free(s);
}

void	debug_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		ft_putstr_fd(map[i], 1);
		i++;
	}
	return ;
}

void	debug_intline(int *line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_intplen(line);
	while (i < len)
	{
		printf("%d", line[i]);
		i++;
	}
	printf("-1\n");
	i++;
}

void	debug_intmap(int **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		debug_intline(map[i]);
		i++;
	}
	printf("kkk = %d\n", map[11][27]);
}
