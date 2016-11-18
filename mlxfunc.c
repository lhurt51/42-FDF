/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxfunc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:45:15 by lhurt             #+#    #+#             */
/*   Updated: 2016/11/03 14:45:25 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void 	draw_y(t_mlx *lst, _3D *point1, _3D *point2, float xans, float yans)
{
	float	m, e;
	int		y1, y2, i, j, inc;

	i = fabs(point1->x);
	y1 = fabs(point1->y);
	y2 = fabs(point2->y);
	m = fabs(xans/yans);
	if (xans > 0)
	{
		inc = 1;
		e = -(1 - (point1->x - i) - (point1->y - y1) * (xans / yans));
	}
	else
	{
		inc = -1;
		e = -((point1->x - i) - (point1->y - y1) * (xans / yans));
	}
	j = y1;
	while (j < y2)
	{
		while (e >= 0)
		{
			i += inc;
			e -= 1.0;
		}
		mlx_pixel_put(lst->mlx, lst->win, i , j, 0xFFFFFF);
		j += 1;
		e += m;
	}
}

void 	draw_x(t_mlx *lst, _3D *point1, _3D *point2, float xans, float yans)
{
	float	m, e;
	int		x1, x2, i, j, inc;

	j = fabs(point1->y);
	x1 = fabs(point1->x);
	x2 = fabs(point2->x);
	m = fabs(xans/yans);
	if (yans > 0)
	{
		inc = 1;
		e = -(1 - (point1->y - j) - (yans * (1 - (point1->x - x1)) / xans));
	}
	else
	{
		inc = -1;
		e = -((point1->y - j) - (point1->x - x1) * (xans / yans));
	}
	i = x1;
	while (i < x2)
	{
		while (e >= 0)
		{
			j += inc;
			e -= 1.0;
		}
		mlx_pixel_put(lst->mlx, lst->win, i , j, 0xFFFFFF);
		i += 1;
		e += m;
	}
}

void 	get_DA(t_mlx *lst, _3D *point1, _3D *point2)
{
	float	xans, yans;

	xans = point2->x - point1->x;
	yans = point2->y - point1->y;
	if (fabs(xans) > fabs(yans))
		draw_x(lst, point1, point2, xans, yans);
	else
		draw_y(lst, point1, point2, xans, yans);
}

void    draw_line(t_mlx *lst, vertex_t **board, unsigned int i, unsigned int j,
	 	unsigned int count)
{
	if (i + 1 < count)
	{
		get_DA(lst, &board[i][j].World, &board[i + 1][j].World);
	}
	if (j + 1 < count)
	{
		get_DA(lst, &board[i][j].World, &board[i][j + 1].World);
	}
}

void    handle_line(t_mlx *lst, vertex_t **board, unsigned int count)
{
	unsigned int i, j;

	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < count)
		{
			mlx_pixel_put(lst->mlx, lst->win, board[i][j].World.x , board[i][j].World.y, 0xFFFFFF);
			draw_line(lst, board, i, j, count);
			j++;
		}
		i++;
	}
}

int		my_key_funct(int keycode, t_mlx *new)
{
	float	tmp[4][4];
	unsigned int i, j;

	if (keycode == 53)
		exit(0);
	else if (keycode == 0)
	{
		MAT_Identity(tmp);
		TR_Rotate(tmp, 10, 0, 0);
		mlx_clear_window(new->mlx, new->win);
		i = 0;
		while (i < 10)
		{
			j = 0;
			while (j < 10)
			{
				VEC_MultMatrix(&new->board[i][j].World, tmp, &new->board[i][j].World);
				j++;
			}
			i++;
		}
		handle_line(new, new->board, 10);
	}
	else
	{
		ft_putstr("This is the keycode: ");
		ft_putnbr(keycode);
		ft_putchar('\n');
	}
	return (0);
}

void 	set_global(vertex_t **board, unsigned int count)
{
	float			tmp[4][4];
	unsigned int	i, j;

	MAT_Identity(tmp);
	TR_Scale(tmp, W_WIDTH / count, W_HEIGHT / count, 0);
	TR_Translate(tmp, W_WIDTH / 2 / count, W_HEIGHT / 2 / count, 0);
	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < count)
		{
			VEC_MultMatrix(&board[i][j].Local, tmp, &board[i][j].World);
			j++;
		}
		i++;
	}
}

void	split_board(vertex_t **board, unsigned int count)
{
	t_mlx			*new;

	new = malloc(sizeof(t_mlx));
	new->mlx = mlx_init();
	new->win = mlx_new_window(new->mlx, W_WIDTH, W_HEIGHT, "42");
	new->board = board;
	set_global(board, count);
	handle_line(new, board, count);
	mlx_key_hook(new->win, my_key_funct, new);
	mlx_loop(new->mlx);
}
