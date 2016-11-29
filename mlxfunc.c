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

void    handle_line(t_mlx *lst, unsigned int h, unsigned int l)
{
	unsigned int i, j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			mlx_pixel_put(lst->mlx, lst->win, lst->board[i][j].Screen.x , lst->board[i][j].Screen.y, 0xFF0000);
			check_for_line(lst, i, j, h, l);
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

void 	reset_world(vertex_t **board, float tmp[4][4], unsigned int h, unsigned int l)
{
	unsigned int	j, i;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < l)
		{
			VEC_MultMatrix(&board[i][j].World, tmp, &board[i][j].World);
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
	ft_putstr("Point1\n");
	ft_putstr("x: ");
	ft_putnbr(board[0][0].Screen.x);
	ft_putstr(" y: ");
	ft_putnbr(board[0][0].Screen.y);
	ft_putchar('\n');
	ft_putstr("Point2\n");
	ft_putstr("x: ");
	ft_putnbr(board[i - 1][j - 1].Screen.x);
	ft_putstr(" y: ");
	ft_putnbr(board[i - 1][j - 1].Screen.y);
	ft_putchar('\n');
}

void 	rotate_a(t_mlx *new)
{
	float			tmp[4][4], tmp1[4][4];

	mlx_clear_window(new->mlx, new->win);
	MAT_Identity(tmp);
	TR_Rotate(tmp, 1, 1, 0);
	TR_Translate(tmp, 950, 575, 0);
	reset_world(new->board, tmp, new->h, new->l);
	MAT_Identity(tmp1);
	TR_Translate(tmp1, -XOrigin, -YOrigin, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	set_screen(new->board, new->h, new->l);
	handle_line(new, new->h, new->l);
}

void 	rotate_d(t_mlx *new)
{
	float			tmp[4][4], tmp1[4][4];

	mlx_clear_window(new->mlx, new->win);
	MAT_Identity(tmp);
	TR_Rotate(tmp, -1, -1, 0);
	TR_Translate(tmp, -150, -175, 0);
	reset_world(new->board, tmp, new->h, new->l);
	MAT_Identity(tmp1);
	TR_Translate(tmp1, -XOrigin, -YOrigin, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	set_screen(new->board, new->h, new->l);
	handle_line(new, new->h, new->l);
}

int		my_key_funct(int keycode, t_mlx *new)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 0)
		rotate_a(new);
	else if (keycode == 2)
		rotate_d(new);
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
	new->h = h;
	new->l = l;
	set_global(board, h, l);
	handle_line(new, h, l);
	mlx_key_hook(new->win, my_key_funct, new);
	mlx_loop(new->mlx);
}
