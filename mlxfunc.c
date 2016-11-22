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

void    check_points(t_mlx *lst, vertex_t **board, unsigned int i, unsigned int j,
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
			check_points(lst, board, i, j, h, l);
			j++;
		}
		i++;
	}
}

void 	set_world(vertex_t **board, float tmp[4][4], unsigned int h, unsigned int l)
{
	unsigned int	j, i;

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
}

void 	set_aligned(vertex_t **board, float tmp[4][4], unsigned int h, unsigned int l)
{
	unsigned int	j, i;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			VEC_MultMatrix(&board[i][j].World, tmp, &board[i][j].Aligned);
			j++;
		}
		i++;
	}
}

void 	set_screen(vertex_t **board, unsigned int h, unsigned int l)
{
	unsigned int	j, i;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			Project(&board[i][j]);
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

	MAT_Identity(tmp);
	TR_Rotate(tmp, 3, 3, 0);
	TR_Scale(tmp, W_WIDTH / l, W_HEIGHT / h, 0);
	TR_Translate(tmp, W_WIDTH / 2 / l + W_WIDTH, W_HEIGHT / 2 / h + W_HEIGHT, -FOCAL_DISTANCE);
	set_world(board, tmp, h, l);
	MAT_Identity(tmp1);
	TR_Translate(tmp1, -XOrigin, -YOrigin, -FOCAL_DISTANCE);
	set_aligned(board, tmp1,h, l);
	set_screen(board, h, l);
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
