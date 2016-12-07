/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basicfunc1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 13:46:32 by lhurt             #+#    #+#             */
/*   Updated: 2016/12/07 13:46:49 by lhurt            ###   ########.fr       */
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

void 	set_perspective(t_mlx *new)
{
	float			tmp[4][4];
	unsigned int	j, i;

	i = 0;
	mat_identity(tmp);
	mat_translate(tmp, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE * 4);
	set_aligned(new->board, tmp, new->h, new->l);
	while (i < new->h)
	{
		j = 0;
		while (j < new->l)
		{
			project(&new->board[i][j]);
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
			vec_multmat(&new->board[i][j].Aligned, tmp, &new->board[i][j].Screen);
			j++;
		}
		i++;
	}
	handle_line(new);
}
