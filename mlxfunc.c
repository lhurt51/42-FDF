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
	float	x1, x2, y1, y2, x, y, p, end;

	x1 = point1->x;
	y1 = point1->y;
	x2 = point2->x;
	y2 = point2->y;
	p = 2 * xans - yans;
	if (y1 > y2)
	{
		x = x2;
		y = y2;
		end = y1;
	}
	else
	{
		x = x1;
		y = y1;
		end = y2;
	}
	while (y < end)
	{
		y++;
		if (p < 0)
		{
			p += 2 * xans;
		}
		else
		{
			x++;
			p += 2 * (xans - yans);
		}
		mlx_pixel_put(lst->mlx, lst->win, x, y, 0xFFFFFF);
	}
}

void 	draw_x(t_mlx *lst, _3D *point1, _3D *point2, float xans, float yans)
{
	float	x1, x2, y1, y2, x, y, p, end;

	x1 = point1->x;
	y1 = point1->y;
	x2 = point2->x;
	y2 = point2->y;
	p = 2 * yans - xans;
	if (x1 > x2)
	{
		x = x2;
		y = y2;
		end = x1;
	}
	else
	{
		x = x1;
		y = y1;
		end = x2;
	}
	while (x < end)
	{
		x++;
		if (p < 0)
		{
			p += 2 * yans;
		}
		else
		{
			y++;
			p += 2 * (yans - xans);
		}
		mlx_pixel_put(lst->mlx, lst->win, x, y, 0xFFFFFF);
	}
}

void 	get_DA(t_mlx *lst, _3D *point1, _3D *point2)
{
	float		xans, yans;

	xans = point1->x - point2->x;
	yans = point1->y - point2->y;
	if (xans > yans)
		draw_x(lst, point1, point2, xans, yans);
	else
		draw_y(lst, point1, point2, xans, yans);
}

void    draw_line(t_mlx *lst, vertex_t **board, unsigned int i, unsigned int j,
	 	unsigned int h, unsigned int l)
{
	if (i + 1 < h)
	{
		get_DA(lst, &board[i][j].Screen, &board[i + 1][j].Screen);
	}
	if (j + 1 < l)
	{
		get_DA(lst, &board[i][j].Screen, &board[i][j + 1].Screen);
	}
}

void    handle_line(t_mlx *lst, vertex_t **board, unsigned int h, unsigned int l)
{
	unsigned int i, j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			mlx_pixel_put(lst->mlx, lst->win, board[i][j].Screen.x , board[i][j].Screen.y, 0xFF0000);
			draw_line(lst, board, i, j, h, l);
			j++;
		}
		i++;
	}
}

int		my_key_funct(int keycode, t_mlx *new)
{
	new = NULL;
	if (keycode == 53)
		exit(0);
	else
	{
		ft_putstr("This is the keycode: ");
		ft_putnbr(keycode);
		ft_putchar('\n');
	}
	return (0);
}

void 	set_global(vertex_t **board, unsigned int h, unsigned int l)
{
	float			tmp[4][4], tmp1[4][4];
	unsigned int	i, j;

	MAT_Identity(tmp);
	TR_Scale(tmp, W_WIDTH / l, W_HEIGHT / h, -1);
	TR_Rotate(tmp, 0, 0, 0);
	TR_Translate(tmp, W_WIDTH / 2 / l, W_HEIGHT / 2 / h, -FOCAL_DISTANCE / 2 / 10);
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			VEC_MultMatrix(&board[i][j].Local, tmp, &board[i][j].World);
			j++;
		}
		i++;
	}
	MAT_Identity(tmp1);
	TR_Translate(tmp1, -XOrigin, -YOrigin, -FOCAL_DISTANCE);
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			VEC_MultMatrix(&board[i][j].World, tmp1, &board[i][j].Aligned);
			Project(&board[i][j]);
			j++;
		}
		i++;
	}
}

void	split_board(vertex_t **board, unsigned int h, unsigned int l)
{
	t_mlx			*new;

	new = malloc(sizeof(t_mlx));
	new->mlx = mlx_init();
	new->win = mlx_new_window(new->mlx, W_WIDTH, W_HEIGHT, "42");
	new->board = board;
	set_global(board, h, l);
	handle_line(new, board, h, l);
	mlx_key_hook(new->win, my_key_funct, new);
	mlx_loop(new->mlx);
}
