/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumatsui <yumatsui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:52:47 by yumatsui          #+#    #+#             */
/*   Updated: 2024/07/09 14:40:06 by yumatsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include "data.h"
# include "functions.h"
# include "key.h"
# include "raycast.h"
# include "minimap.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define OK 1
# define ERROR 0
# define MALLOCERROR -1
# include "../srcs/libft/libft.h"

# define NORTH 4
# define SOUTH 5
# define WEST 6
# define EAST 7

#endif