/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extrafunc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 11:53:30 by lhurt             #+#    #+#             */
/*   Updated: 2016/12/06 11:53:32 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			invert(t_mlx *new)
{
	float	tmp[4][4];
	float	tmp1[4][4];
	float	tmp2[4][4];

	mat_identity(tmp);
	mat_scale(tmp, -1, -1, -1);
	reset_world(new->board, tmp, new->h, new->l);
	mat_identity(tmp1);
	mat_translate(tmp1, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	mat_identity(tmp2);
	set_screen(new, tmp2);
}

unsigned int	count_lines(char **str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
