/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookfunc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:59:25 by lhurt             #+#    #+#             */
/*   Updated: 2016/12/12 15:59:37 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_out(t_mlx *new)
{
	float	tmp[4][4];
	float	tmp1[4][4];
	float	tmp2[4][4];

	mat_identity(tmp);
	mat_translate(tmp, -(new->board[0][0].world.x +
		new->board[new->h - 1][new->l - 1].world.x) / 2,
		-(new->board[0][0].world.y +
		new->board[new->h - 1][new->l - 1].world.y) / 2,
		-(new->board[0][0].world.z +
		new->board[new->h - 1][new->l - 1].world.z) / 2);
	mat_scale(tmp, 0.9, 0.9, 0.9);
	reset_world(new->board, tmp, new->h, new->l);
	mat_identity(tmp1);
	mat_translate(tmp1, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	mat_identity(tmp2);
	set_screen(new, tmp2);
}

void	zoom_in(t_mlx *new)
{
	float	tmp[4][4];
	float	tmp1[4][4];
	float	tmp2[4][4];

	mat_identity(tmp);
	mat_translate(tmp, -(new->board[0][0].world.x +
		new->board[new->h - 1][new->l - 1].world.x) / 2,
		-(new->board[0][0].world.y +
		new->board[new->h - 1][new->l - 1].world.y) / 2,
		-(new->board[0][0].world.z +
		new->board[new->h - 1][new->l - 1].world.z) / 2);
	mat_scale(tmp, 1.1, 1.1, 1.1);
	reset_world(new->board, tmp, new->h, new->l);
	mat_identity(tmp1);
	mat_translate(tmp1, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	mat_identity(tmp2);
	set_screen(new, tmp2);
}

void	invert_z(t_mlx *new)
{
	float	tmp[4][4];
	float	tmp1[4][4];
	float	tmp2[4][4];

	mat_identity(tmp);
	mat_translate(tmp, -(new->board[0][0].world.x +
		new->board[new->h - 1][new->l - 1].world.x) / 2,
		-(new->board[0][0].world.y +
		new->board[new->h - 1][new->l - 1].world.y) / 2,
		-(new->board[0][0].world.z +
		new->board[new->h - 1][new->l - 1].world.z) / 2);
	mat_scale(tmp, 1, 1, -1);
	reset_world(new->board, tmp, new->h, new->l);
	mat_identity(tmp1);
	mat_translate(tmp1, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	mat_identity(tmp2);
	set_screen(new, tmp2);
}
