/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basicfunc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 11:50:10 by lhurt             #+#    #+#             */
/*   Updated: 2016/12/06 11:50:11 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_world(t_vertex **board, float tmp[4][4], unsigned int h,
	unsigned int l)
{
	unsigned int	j;
	unsigned int	i;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			vec_multmat(&board[i][j].local, tmp, &board[i][j].world);
			j++;
		}
		i++;
	}
}

void	reset_world(t_vertex **board, float tmp[4][4], unsigned int h,
	unsigned int l)
{
	t_3d			tmp3d;
	unsigned int	j;
	unsigned int	i;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			tmp3d = board[i][j].world;
			vec_multmat(&tmp3d, tmp, &board[i][j].world);
			j++;
		}
		i++;
	}
}

void	set_aligned(t_vertex **board, float tmp[4][4], unsigned int h,
	unsigned int l)
{
	unsigned int	j;
	unsigned int	i;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			vec_multmat(&board[i][j].world, tmp, &board[i][j].aligned);
			j++;
		}
		i++;
	}
}
