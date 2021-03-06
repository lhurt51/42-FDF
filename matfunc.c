/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matfunc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 18:06:27 by lhurt             #+#    #+#             */
/*   Updated: 2016/12/06 18:06:30 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mat_identity(float mat[4][4])
{
	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = 0;
	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[1][3] = 0;
	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	mat[2][3] = 0;
	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
}

void	mat_translate(float matrix[4][4], float tx, float ty, float tz)
{
	float	tmat[4][4];
	float	tmp[4][4];

	tmat[0][0] = 1;
	tmat[0][1] = 0;
	tmat[0][2] = 0;
	tmat[0][3] = 0;
	tmat[1][0] = 0;
	tmat[1][1] = 1;
	tmat[1][2] = 0;
	tmat[1][3] = 0;
	tmat[2][0] = 0;
	tmat[2][1] = 0;
	tmat[2][2] = 1;
	tmat[2][3] = 0;
	tmat[3][0] = tx;
	tmat[3][1] = ty;
	tmat[3][2] = tz;
	tmat[3][3] = 1;
	mat_mult(matrix, tmat, tmp);
	mat_copy(tmp, matrix);
}

void	mat_scale(float matrix[4][4], float sx, float sy, float sz)
{
	float	smat[4][4];
	float	tmp[4][4];

	smat[0][0] = sx;
	smat[0][1] = 0;
	smat[0][2] = 0;
	smat[0][3] = 0;
	smat[1][0] = 0;
	smat[1][1] = sy;
	smat[1][2] = 0;
	smat[1][3] = 0;
	smat[2][0] = 0;
	smat[2][1] = 0;
	smat[2][2] = sz;
	smat[2][3] = 0;
	smat[3][0] = 0;
	smat[3][1] = 0;
	smat[3][2] = 0;
	smat[3][3] = 1;
	mat_mult(matrix, smat, tmp);
	mat_copy(tmp, matrix);
}

void	project(t_vertex *vertex)
{
	if (!vertex->aligned.z)
		vertex->aligned.z = 1;
	vertex->screen.x = FOCAL_DISTANCE * vertex->aligned.x / vertex->aligned.z +
	W_XORIGIN;
	vertex->screen.y = FOCAL_DISTANCE * vertex->aligned.y / vertex->aligned.z +
	W_YORIGIN;
}
