/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_assignment_all.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:55:09 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/07/07 14:09:30 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

// is assignment texture_path ok?
static int	assignment_textures_ok(t_analyze *data)
{
	if (!(data->n_texture_path) || !(data->s_texture_path)
		|| !(data->w_texture_path) || !(data->e_texture_path))
		return (0);
	if ((data->f_rgb.r == -1) || (data->c_rgb.r == -1))
		return (0);
	return (1);
}

int	check_map(char **map)
{
	int	i;
	int	j;
	int	position_flag;

	i = 0;
	position_flag = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E'
				&& map[i][j] != ' ' && map[i][j] != '\n')
				return (0);
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
				|| map[i][j] == 'E')
				position_flag += 1;
			j++;
		}
		i++;
	}
	if (position_flag != 1)
		return (0);
	return (1);
}

t_position	assignment_all(t_analyze *data, char *filepath)
{
	int		fd;
	char	*line;
	char	**map;

	fd = open(filepath, O_RDONLY);
	map = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!assignment_textures_ok(data))
		{
			assignment_texture(data, line);
			assignment_rgb(data, line);
		}
		else
			map = ft_strppjoin(map, line);
		free(line);
	}
	close(fd);
	if (check_map(map))
		return (assignment_map(data, map), analyze_map(data->map));
	write(1, "Error\n", 6);
	exit(0);
}
