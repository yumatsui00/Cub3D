/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_assignment_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:48:19 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/07/06 10:12:48 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	*tranlate_str2int(char *line, int max_width)
{
	int	*ret;
	int	i;

	ret = (int *)malloc(sizeof(int) * (max_width + 3));
	if (!ret)
		return (NULL);
	i = 0;
	ret[0] = 9;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
			ret[i + 1] = line[i] - '0';
		else if (line[i] == ' ')
			ret[i + 1] = 9;
		else if (line[i] == '\n')
			ret[i + 1] = -1;
		else if (line[i] == 'N')
			ret[i + 1] = NORTH;
		else if (line[i] == 'S')
			ret[i + 1] = SOUTH;
		else if (line[i] == 'W')
			ret[i + 1] = WEST;
		else if (line[i] == 'E')
			ret[i + 1] = EAST;
		i++;
	}
	while (i < max_width + 1)
	{
		ret[i] = 9;
		i++;
	}
	ret[i] = -1;
	return (ret);
}

// make intmap
void	assignment_map(t_analyze *data, char **map)
{
	int	i;
	int	*int_line;
	int	max_width;

	i = 0;
	max_width = get_max_width_charpp(map);
	data->map = ft_intppjoin(data->map, make_off_line(max_width, 9));
	while (map[i])
	{
		int_line = tranlate_str2int(map[i], max_width);
		data->map = ft_intppjoin(data->map, int_line);
		i++;
	}
	data->map = ft_intppjoin(data->map, make_off_line(max_width, -1));
}
