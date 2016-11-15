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
#include <stdio.h>

int		my_key_funct(int keycode, t_mlx *new)
{
	if (keycode == 53)
		exit(0);
	else if (new->win)
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

void    draw_line(t_mlx *lst, vertex_t **board, unsigned int i, unsigned int j,
	 	unsigned int count)
{
	float	xans, yans, slope, solution, y1, y2, x1, x2;
	int		sign;

	sign = 1;
	y1 = board[i][j].World.y;
	x1 = board[i][j].World.x;
	
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

void	split_board(vertex_t **board, unsigned int count)
{
	t_mlx			*new;
	unsigned int	i;

	i = 0;
	new = malloc(sizeof(t_mlx));
	new->mlx = mlx_init();
	new->win = mlx_new_window(new->mlx, W_WIDTH, W_HEIGHT, "42");
	set_global(board, count);
	handle_line(new, board, count);
	mlx_key_hook(new->win, my_key_funct, new);
	mlx_loop(new->mlx);
}
