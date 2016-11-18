/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 15:55:03 by lhurt             #+#    #+#             */
/*   Updated: 2016/10/21 15:55:04 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include "libft/libft.h"

#define FOCAL_DISTANCE 200
#define W_WIDTH 2502
#define W_HEIGHT 1388
#define XOrigin 1251
#define YOrigin 694

float           matrix[4][4];

typedef struct
{
    short x, y;
}   _2D;

typedef struct
{
    float x, y, z;
}   _3D;

typedef struct
{
    _3D Local;
    _3D World;
    _3D Aligned;
}   vertex_t;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
    void        *img;
	vertex_t    **board;
}				t_mlx;

void	test_func(void);
void	split_board(vertex_t **board, unsigned int count);
void    MAT_Identity(float mat[4][4]);
void    MAT_Copy(float source[4][4], float dest[4][4]);
void    MAT_Mult(float mat1[4][4], float mat2[4][4], float dest[4][4]);
void    VEC_MultMatrix(_3D *Source, float mat[4][4], _3D *Dest);
void    TR_Translate(float matrix[4][4], float tx, float ty, float tz);
void    TR_Scale(float matrix[4][4], float sx, float sy, float sz);
void    TR_Rotate(float matrix[4][4], int ax, int ay, int az);

#endif
