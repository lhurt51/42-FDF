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

# include <mlx.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "libft/libft.h"

# define FOCAL_DISTANCE 200
# define W_WIDTH 1920
# define W_HEIGHT 1080
# define W_XORIGIN W_WIDTH / 2
# define W_YORIGIN W_HEIGHT / 2

typedef struct		s_3d
{
	float			x;
	float			y;
	float			z;
}					t_3d;

typedef struct		s_vertex
{
	t_3d			local;
	t_3d			world;
	t_3d			aligned;
	t_3d			screen;
}					t_vertex;

typedef struct		s_line
{
	int				inc;
	float			yans;
	float			xans;
}					t_line;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	unsigned int	h;
	unsigned int	l;
	t_vertex		**board;
}					t_mlx;

void				mat_identity(float mat[4][4]);
void				mat_copy(float source[4][4], float dest[4][4]);
void				mat_mult(float mat1[4][4], float mat2[4][4],
						float dest[4][4]);
void				vec_multmat(t_3d *source, float mat[4][4], t_3d *dest);
void				mat_translate(float matrix[4][4], float tx, float ty,
						float tz);
void				mat_scale(float matrix[4][4], float sx, float sy, float sz);
void				mat_rotate(float matrix[4][4], float ax, float ay,
						float az);
void				project(t_vertex *vertex);
void				rotate_a(t_mlx *new);
void				rotate_d(t_mlx *new);
void				rotate_w(t_mlx *new);
void				rotate_s(t_mlx *new);
void				rotate_q(t_mlx *new);
void				rotate_e(t_mlx *new);
void				zoom_out(t_mlx *new);
void				zoom_in(t_mlx *new);
void				invert_z(t_mlx *new);
void				set_global(t_mlx *new);
void				set_world(t_vertex **board, float tmp[4][4], unsigned int h,
						unsigned int l);
void				reset_world(t_vertex **board, float tmp[4][4],
						unsigned int h, unsigned int l);
void				set_aligned(t_vertex **board, float tmp[4][4],
						unsigned int h, unsigned int l);
void				set_perspective(t_mlx *new);
void				set_screen(t_mlx *new, float tmp[4][4]);
void				set_parallel(t_mlx *new);
void				invert(t_mlx *new);
unsigned int		count_lines(char **str);
void				run_win(t_vertex **board, unsigned int h, unsigned int l);
void				check_for_line(t_mlx *lst, unsigned int i, unsigned int j);

#endif
