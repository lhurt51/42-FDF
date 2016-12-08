/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotfunc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 17:27:59 by lhurt             #+#    #+#             */
/*   Updated: 2016/12/06 17:28:02 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rot_xaxis(float tmp1[4][4], float tmp2[4][4], float ax)
{
	float	xmat[4][4];

	xmat[0][0] = 1;
	xmat[0][1] = 0;
	xmat[0][2] = 0;
	xmat[0][3] = 0;
	xmat[1][0] = 0;
	xmat[1][1] = cos(ax);
	xmat[1][2] = sin(ax);
	xmat[1][3] = 0;
	xmat[2][0] = 0;
	xmat[2][1] = -sin(ax);
	xmat[2][2] = cos(ax);
	xmat[2][3] = 0;
	xmat[3][0] = 0;
	xmat[3][1] = 0;
	xmat[3][2] = 0;
	xmat[3][3] = 1;
	mat_mult(tmp1, xmat, tmp2);
}

void	rot_yaxis(float tmp1[4][4], float tmp2[4][4], float ay)
{
	float	ymat[4][4];

	ymat[0][0] = cos(ay);
	ymat[0][1] = 0;
	ymat[0][2] = -sin(ay);
	ymat[0][3] = 0;
	ymat[1][0] = 0;
	ymat[1][1] = 1;
	ymat[1][2] = 0;
	ymat[1][3] = 0;
	ymat[2][0] = sin(ay);
	ymat[2][1] = 0;
	ymat[2][2] = cos(ay);
	ymat[2][3] = 0;
	ymat[3][0] = 0;
	ymat[3][1] = 0;
	ymat[3][2] = 0;
	ymat[3][3] = 1;
	mat_mult(tmp1, ymat, tmp2);
}

void	rot_zaxis(float tmp1[4][4], float tmp2[4][4], float az)
{
	float	zmat[4][4];

	zmat[0][0] = cos(az);
	zmat[0][1] = sin(az);
	zmat[0][2] = 0;
	zmat[0][3] = 0;
	zmat[1][0] = -sin(az);
	zmat[1][1] = cos(az);
	zmat[1][2] = 0;
	zmat[1][3] = 0;
	zmat[2][0] = 0;
	zmat[2][1] = 0;
	zmat[2][2] = 1;
	zmat[2][3] = 0;
	zmat[3][0] = 0;
	zmat[3][1] = 0;
	zmat[3][2] = 0;
	zmat[3][3] = 1;
	mat_mult(tmp1, zmat, tmp2);
}

void	mat_rotate(float matrix[4][4], float ax, float ay, float az)
{
	float	mat1[4][4];
	float	mat2[4][4];

	rot_yaxis(matrix, mat1, ay);
	rot_xaxis(mat1, mat2, ax);
	rot_zaxis(mat2, matrix, az);
}
