/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookfunc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 11:47:19 by lhurt             #+#    #+#             */
/*   Updated: 2016/12/06 11:47:22 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_a(t_mlx *new)
{
	float	tmp[4][4];
	float	tmp1[4][4];
	float	tmp2[4][4];

	mat_identity(tmp);
	mat_translate(tmp, -(new->board[0][0].world.x +
		new->board[new->h - 1][new->l - 1].world.x) / 2,
		-(new->board[0][0].world.y +
		new->board[new->h - 1][new->l - 1].world.y) / 2, 0);
	mat_rotate(tmp, 0, (M_PI / 200), 0);
	reset_world(new->board, tmp, new->h, new->l);
	mat_identity(tmp1);
	mat_translate(tmp1, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	mat_identity(tmp2);
	set_screen(new, tmp2);
}

void	rotate_d(t_mlx *new)
{
	float	tmp[4][4];
	float	tmp1[4][4];
	float	tmp2[4][4];

	mat_identity(tmp);
	mat_translate(tmp, -(new->board[0][0].world.x +
		new->board[new->h - 1][new->l - 1].world.x) / 2,
		-(new->board[0][0].world.y +
		new->board[new->h - 1][new->l - 1].world.y) / 2, 0);
	mat_rotate(tmp, 0, -(M_PI / 200), 0);
	reset_world(new->board, tmp, new->h, new->l);
	mat_identity(tmp1);
	mat_translate(tmp1, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	mat_identity(tmp2);
	set_screen(new, tmp2);
}

void	rotate_w(t_mlx *new)
{
	float	tmp[4][4];
	float	tmp1[4][4];
	float	tmp2[4][4];

	mat_identity(tmp);
	mat_translate(tmp, -(new->board[0][0].world.x +
		new->board[new->h - 1][new->l - 1].world.x) / 2,
		-(new->board[0][0].world.y +
		new->board[new->h - 1][new->l - 1].world.y) / 2, 0);
	mat_rotate(tmp, (M_PI / 200), 0, 0);
	reset_world(new->board, tmp, new->h, new->l);
	mat_identity(tmp1);
	mat_translate(tmp1, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	mat_identity(tmp2);
	set_screen(new, tmp2);
}
