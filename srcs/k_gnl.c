/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_gnl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:53:39 by kkomatsu          #+#    #+#             */
/*   Updated: 2024/07/09 14:01:45 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

static char	*ft_strjoin_c(char *s, char c)
{
	char	*ret;
	int		i;

	if (!s)
	{
		ret = (char *)malloc(2);
		if (!ret)
			return (NULL);
		ret[0] = c;
		ret[1] = '\0';
		return (ret);
	}
	i = -1;
	ret = (char *)malloc(ft_strlen(s) + 2);
	if (!ret)
		return (NULL);
	while (s[++i])
		ret[i] = s[i];
	ret[i] = c;
	ret[i + 1] = '\0';
	free(s);
	return (ret);
}

char	*get_next_line(int fd)
{
	int n;
	char c;
	char *ret;

	c = '\0';
	ret = NULL;
	while (c != '\n')
	{
		n = read(fd, &c, 1);
		if (n <= 0)
			break ;
		ret = ft_strjoin_c(ret, c);
	}
	return (ret);
}