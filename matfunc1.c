/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basicmatfunc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 18:02:57 by lhurt             #+#    #+#             */
/*   Updated: 2016/12/06 18:03:00 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//Copying a maxtrix to another.
void mat_copy(float source[4][4], float dest[4][4])
{
    int i,j;

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            dest[i][j] = source[i][j];
            j++;
        }
        i++;
    }
}

//Multiplying two matricies together.
void mat_mult(float matA[4][4], float matB[4][4], float dest[4][4])
{
    int i,j;

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            dest[i][j] = matA[i][0] * matB[0][j] + matA[i][1] * matB[1][j] +
                matA[i][2] * matB[2][j] + matA[i][3] * matB[3][j];
            j++;
        }
        i++;
    }
}

// Multiplying vectors with a matrix???? still a bit confused on why & how.
void vec_multmat(_3D *Source, float mat[4][4], _3D *Dest)
{
    Dest->x = Source->x * mat[0][0] + Source->y * mat[1][0]
        + Source->z * mat[2][0] + mat[3][0];
    Dest->y = Source->x * mat[0][1] + Source->y * mat[1][1]
        + Source->z * mat[2][1] + mat[3][1];
    Dest->z = Source->x * mat[0][2] + Source->y * mat[1][2]
        + Source->z * mat[2][2] + mat[3][2];
}
