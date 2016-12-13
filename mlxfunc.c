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

void	extra_hooks(int keycode, t_mlx *new)
{
	if (keycode == 69)
		zoom_in(new);
	else if (keycode == 78)
		zoom_out(new);
}

int		my_key_press(int keycode, t_mlx *new)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 0)
		rotate_a(new);
	else if (keycode == 2)
		rotate_d(new);
	else if (keycode == 13)
		rotate_w(new);
	else if (keycode == 1)
		rotate_s(new);
	else if (keycode == 12)
		rotate_q(new);
	else if (keycode == 14)
		rotate_e(new);
	else if (keycode == 35)
		set_perspective(new);
	else if (keycode == 31)
		set_parallel(new);
	else if (keycode == 36)
		invert(new);
	else if (keycode == 257)
		set_global(new);
	else
		extra_hooks(keycode, new);
	return (0);
}

void	set_global(t_mlx *new)
{
	float	tmp[4][4];
	float	tmp1[4][4];
	float	tmp2[4][4];

	mat_identity(tmp);
	mat_translate(tmp, -(new->board[0][0].local.x +
		new->board[new->h - 1][new->l - 1].local.x) / 2,
		-(new->board[0][0].local.y +
		new->board[new->h - 1][new->l - 1].local.y) / 2, 0);
	mat_scale(tmp, W_HEIGHT / new->h, W_HEIGHT / new->h, 10);
	set_world(new->board, tmp, new->h, new->l);
	mat_identity(tmp1);
	mat_translate(tmp1, W_XORIGIN, W_YORIGIN, -FOCAL_DISTANCE);
	set_aligned(new->board, tmp1, new->h, new->l);
	mat_identity(tmp2);
	set_screen(new, tmp2);
}

void	run_win(t_vertex **board, unsigned int h, unsigned int l)
{
	t_mlx			*new;

	new = malloc(sizeof(t_mlx));
	new->mlx = mlx_init();
	new->win = mlx_new_window(new->mlx, W_WIDTH, W_HEIGHT, "42");
	new->board = board;
	new->h = h;
	new->l = l;
	set_global(new);
	mlx_hook(new->win, 2, 0, my_key_press, new);
	mlx_loop(new->mlx);
}
