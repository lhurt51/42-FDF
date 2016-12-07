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

void 	rotate_a(t_mlx *new)
{
	float			tmp[4][4], tmp1[4][4], tmp2[4][4];

	MAT_Identity(tmp);
	TR_Rotate(tmp, 0, (M_PI / 200), 0);
	reset_world(new->board, tmp, new->h, new->l);
	MAT_Identity(tmp1);
	TR_Translate(tmp1, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	MAT_Identity(tmp2);
	set_screen(new, tmp2);
}

void 	rotate_d(t_mlx *new)
{
	float			tmp[4][4], tmp1[4][4], tmp2[4][4];

	MAT_Identity(tmp);
	TR_Rotate(tmp, 0, -(M_PI / 200), 0);
	reset_world(new->board, tmp, new->h, new->l);
	MAT_Identity(tmp1);
	TR_Translate(tmp1, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	MAT_Identity(tmp2);
	set_screen(new, tmp2);
}

void 	rotate_w(t_mlx *new)
{
	float			tmp[4][4], tmp1[4][4], tmp2[4][4];

	MAT_Identity(tmp);
	TR_Rotate(tmp, (M_PI / 200), 0, 0);
	reset_world(new->board, tmp, new->h, new->l);
	MAT_Identity(tmp1);
	TR_Translate(tmp1, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	MAT_Identity(tmp2);
	set_screen(new, tmp2);
}

void 	rotate_s(t_mlx *new)
{
	float			tmp[4][4], tmp1[4][4], tmp2[4][4];

	MAT_Identity(tmp);
	TR_Rotate(tmp, -(M_PI / 200), 0, 0);
	reset_world(new->board, tmp, new->h, new->l);
	MAT_Identity(tmp1);
	TR_Translate(tmp1, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	MAT_Identity(tmp2);
	set_screen(new, tmp2);
}

void 	rotate_q(t_mlx *new)
{
	float			tmp[4][4], tmp1[4][4], tmp2[4][4];

	MAT_Identity(tmp);
	TR_Rotate(tmp, 0, 0, (M_PI / 200));
	reset_world(new->board, tmp, new->h, new->l);
	MAT_Identity(tmp1);
	TR_Translate(tmp1, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	MAT_Identity(tmp2);
	set_screen(new, tmp2);
}

void 	rotate_e(t_mlx *new)
{
	float			tmp[4][4], tmp1[4][4], tmp2[4][4];

	MAT_Identity(tmp);
	TR_Rotate(tmp, 0, 0, -(M_PI / 200));
	reset_world(new->board, tmp, new->h, new->l);
	MAT_Identity(tmp1);
	TR_Translate(tmp1, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	MAT_Identity(tmp2);
	set_screen(new, tmp2);
}

void 	set_parallel(t_mlx *new)
{
	float			tmp[4][4], tmp1[4][4];

	MAT_Identity(tmp);
	TR_Translate(tmp, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp, new->h, new->l);
	MAT_Identity(tmp1);
	set_screen(new, tmp1);
}
