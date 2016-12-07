/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookfunc1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 13:49:52 by lhurt             #+#    #+#             */
/*   Updated: 2016/12/07 13:50:06 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void 	rotate_s(t_mlx *new)
{
	float			tmp[4][4], tmp1[4][4], tmp2[4][4];

	mat_identity(tmp);
	mat_rotate(tmp, -(M_PI / 200), 0, 0);
	reset_world(new->board, tmp, new->h, new->l);
	mat_identity(tmp1);
	mat_translate(tmp1, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	mat_identity(tmp2);
	set_screen(new, tmp2);
}

void 	rotate_q(t_mlx *new)
{
	float			tmp[4][4], tmp1[4][4], tmp2[4][4];

	mat_identity(tmp);
	mat_rotate(tmp, 0, 0, (M_PI / 200));
	reset_world(new->board, tmp, new->h, new->l);
	mat_identity(tmp1);
	mat_translate(tmp1, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	mat_identity(tmp2);
	set_screen(new, tmp2);
}

void 	rotate_e(t_mlx *new)
{
	float			tmp[4][4], tmp1[4][4], tmp2[4][4];

	mat_identity(tmp);
	mat_rotate(tmp, 0, 0, -(M_PI / 200));
	reset_world(new->board, tmp, new->h, new->l);
	mat_identity(tmp1);
	mat_translate(tmp1, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	mat_identity(tmp2);
	set_screen(new, tmp2);
}

void 	set_parallel(t_mlx *new)
{
	float			tmp[4][4], tmp1[4][4];

	mat_identity(tmp);
	mat_translate(tmp, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp, new->h, new->l);
	mat_identity(tmp1);
	set_screen(new, tmp1);
}
