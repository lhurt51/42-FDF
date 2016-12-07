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
    //Identity matrix

	mat[0][0]=1;
	mat[0][1]=0;
	mat[0][2]=0;
	mat[0][3]=0;
	mat[1][0]=0;
	mat[1][1]=1;
	mat[1][2]=0;
	mat[1][3]=0;
	mat[2][0]=0;
	mat[2][1]=0;
	mat[2][2]=1;
	mat[2][3]=0;
	mat[3][0]=0;
	mat[3][1]=0;
	mat[3][2]=0;
	mat[3][3]=1;
}

//This is to translate a matrix base on the vector we use
void	mat_translate(float matrix[4][4], float tx, float ty, float tz)
{
   float tmat[4][4], tmp[4][4];

   //Translation matrix;
	tmat[0][0]=1;
	tmat[0][1]=0;
	tmat[0][2]=0;
	tmat[0][3]=0;
	tmat[1][0]=0;
	tmat[1][1]=1;
	tmat[1][2]=0;
	tmat[1][3]=0;
	tmat[2][0]=0;
	tmat[2][1]=0;
	tmat[2][2]=1;
	tmat[2][3]=0;
	tmat[3][0]=tx;
	tmat[3][1]=ty;
	tmat[3][2]=tz;
	tmat[3][3]=1;
   //First we must copy the translation into mat1 so we dont destroy data
   mat_mult(matrix, tmat, tmp);
   //Then we copy back into matrix and return indirrectly
   mat_copy(tmp, matrix);
}

//this can make my matrix scale to any size i want
void	mat_scale(float matrix[4][4], float sx, float sy, float sz)
{
    float smat[4][4], tmp[4][4];

    //scalular matrix
    smat[0][0]=sx;
	smat[0][1]=0;
	smat[0][2]=0;
	smat[0][3]=0;
    smat[1][0]=0;
	smat[1][1]=sy;
	smat[1][2]=0;
	smat[1][3]=0;
    smat[2][0]=0;
	smat[2][1]=0;
	smat[2][2]=sz;
	smat[2][3]=0;
    smat[3][0]=0;
	smat[3][1]=0;
	smat[3][2]=0;
	smat[3][3]=1;
    //First we must copy the scale into mat1 so we dont destroy data
    mat_mult(matrix, smat, tmp);
    //Then we copy back into matrix and return indirrectly
    mat_copy(tmp, matrix);
}

void 	project(vertex_t *Vertex)
{
    if(!Vertex->Aligned.z)
        Vertex->Aligned.z = 1;
    //Projection formula
    Vertex->Screen.x = FOCAL_DISTANCE * Vertex->Aligned.x / Vertex->Aligned.z + W_XORIGIN;
    Vertex->Screen.y = FOCAL_DISTANCE * Vertex->Aligned.y / Vertex->Aligned.z + W_YORIGIN;
}
