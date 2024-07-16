/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_assignment_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomatsu <kkomatsu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:31:45 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/07/16 09:58:20 by kkomatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

static int	check_rgb(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && s[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	ret_rgb(char *line, t_rgb *item)
{
	char	**splits;

	splits = ft_split(line, ',');
	if (!splits || !*splits)
		return (0);
	if (!splits[0] || !splits[1] || !splits[2] || ft_strpplen(splits) != 3)
		return (free_double_ptr(splits), 0);
	if (!check_rgb(splits[0]) || !check_rgb(splits[1]) || !check_rgb(splits[2]))
		return (0);
	item->r = ft_atoi(splits[0]);
	item->g = ft_atoi(splits[1]);
	item->b = ft_atoi(splits[2]);
	free_double_ptr(splits);
	if (item->r > 255 || item->g > 255 || item->b > 255)
		(write(1, "Error\n", 6), exit(0));
	return (1);
}

void	is_exist(t_analyze *data, char *s)
{
	if (!ft_strcmp(s, "NO") && data->n_texture_path != NULL)
		(write(1, "Error\n", 6), exit(0));
	else if (!ft_strcmp(s, "SO") && data->s_texture_path != NULL)
		(write(1, "Error\n", 6), exit(0));
	else if (!ft_strcmp(s, "WE") && data->w_texture_path != NULL)
		(write(1, "Error\n", 6), exit(0));
	else if (!ft_strcmp(s, "EA") && data->e_texture_path != NULL)
		(write(1, "Error\n", 6), exit(0));
	else if (!ft_strcmp(s, "F") && data->f_rgb.r != -1)
		(write(1, "Error\n", 6), exit(0));
	else if (!ft_strcmp(s, "C") && data->c_rgb.r != -1)
		(write(1, "Error\n", 6), exit(0));
}

void	assignment_texture(t_analyze *data, char *line)
{
	char	**splits;

	splits = ft_split(line, ' ');
	if (!splits || !*splits || ft_strpplen(splits) != 2)
		return ;
	if (!splits[0] || !splits[1])
		return (free_double_ptr(splits));
	is_exist(data, splits[0]);
	if (!ft_strcmp(splits[0], "NO"))
		return (data->n_texture_path = ft_strdup(splits[1]),
			free_double_ptr(splits));
	else if (!ft_strcmp(splits[0], "SO"))
		return (data->s_texture_path = ft_strdup(splits[1]),
			free_double_ptr(splits));
	else if (!ft_strcmp(splits[0], "WE"))
		return (data->w_texture_path = ft_strdup(splits[1]),
			free_double_ptr(splits));
	else if (!ft_strcmp(splits[0], "EA"))
		return (data->e_texture_path = ft_strdup(splits[1]),
			free_double_ptr(splits));
	return (free_double_ptr(splits));
}

void	assignment_rgb(t_analyze *data, char *line)
{
	char	**splits;

	splits = ft_split(line, ' ');
	if (!splits || !*splits || !ft_strcmp(splits[0], "\n"))
		return ;
	if (ft_strpplen(splits) != 2)
		(write(1, "Error\n", 6), free_double_ptr(splits), exit(0));
	if (!splits[0] || !splits[1])
		return (free_double_ptr(splits));
	if (!ft_strcmp(splits[0], "F"))
		return (ret_rgb(splits[1], &(data->f_rgb)), free_double_ptr(splits));
	else if (!ft_strcmp(splits[0], "C"))
		return (ret_rgb(splits[1], &(data->c_rgb)), free_double_ptr(splits));
	else if (ft_strcmp(splits[0], "NO") && ft_strcmp(splits[0], "SO")
		&& ft_strcmp(splits[0], "WE") && ft_strcmp(splits[0], "EA"))
		(write(1, "Error\n", 6), free_double_ptr(splits), exit(0));
	return (free_double_ptr(splits));
}
