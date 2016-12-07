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

void 	set_world(vertex_t **board, float tmp[4][4], unsigned int h, unsigned int l)
{
	unsigned int	j, i;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			vec_multmat(&board[i][j].Local, tmp, &board[i][j].World);
			j++;
		}
		i++;
	}
}

void 	reset_world(vertex_t **board, float tmp[4][4], unsigned int h, unsigned int l)
{
	_3D				tmp3d;
	unsigned int	j, i;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			tmp3d = board[i][j].World;
			vec_multmat(&tmp3d, tmp, &board[i][j].World);
			j++;
		}
		i++;
	}
}

void 	set_aligned(vertex_t **board, float tmp[4][4], unsigned int h, unsigned int l)
{
	unsigned int	j, i;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			vec_multmat(&board[i][j].World, tmp, &board[i][j].Aligned);
			j++;
		}
		i++;
	}
}
