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

void    handle_line(t_mlx *lst)
{
	unsigned int i, j;

	i = 0;
	mlx_clear_window(lst->mlx, lst->win);
	while (i < lst->h)
	{
		j = 0;
		while (j < lst->l)
		{
			mlx_pixel_put(lst->mlx, lst->win, lst->board[i][j].Screen.x , lst->board[i][j].Screen.y, 0xFF0000);
			check_for_line(lst, i, j);
			j++;
		}
		i++;
	}
}

void 	set_world(vertex_t **board, float tmp[4][4], unsigned int h, unsigned int l)
{
	unsigned int	j, i;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			VEC_MultMatrix(&board[i][j].Local, tmp, &board[i][j].World);
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
			VEC_MultMatrix(&tmp3d, tmp, &board[i][j].World);
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
			VEC_MultMatrix(&board[i][j].World, tmp, &board[i][j].Aligned);
			j++;
		}
		i++;
	}
}

void 	set_perspective(t_mlx *new)
{
	float			tmp[4][4];
	unsigned int	j, i;

	i = 0;
	MAT_Identity(tmp);
	TR_Translate(tmp, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE * 3);
	set_aligned(new->board, tmp, new->h, new->l);
	while (i < new->h)
	{
		j = 0;
		while (j < new->l)
		{
			Project(&new->board[i][j]);
			j++;
		}
		i++;
	}
	handle_line(new);
}

void 	set_screen(t_mlx *new, float tmp[4][4])
{
	unsigned int	j, i;

	i = 0;
	while (i < new->h)
	{
		j = 0;
		while (j < new->l)
		{
			VEC_MultMatrix(&new->board[i][j].Aligned, tmp, &new->board[i][j].Screen);
			j++;
		}
		i++;
	}
	handle_line(new);
}
