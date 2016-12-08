/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 19:21:13 by lhurt             #+#    #+#             */
/*   Updated: 2016/11/21 19:23:15 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void 	draw_y(t_mlx *lst, t_3d *point1, t_3d *point2, float xans, float yans)
{
	int		x, y, p, inc;

	x = point1->x;
	y = point1->y;
	p = 2 * xans - yans;
	if (x < (int)point2->x)
		inc = 1;
	else
		inc = -1;
	while (y < (int)point2->y)
	{
		mlx_pixel_put(lst->mlx, lst->win, x, y, 0xFFFFFF);
		if (p < 0)
		{
			p += 2 * xans;
		}
		else
		{
			x += inc;
			p += 2 * (xans - yans);
		}
		y++;
	}
}

void 	draw_x(t_mlx *lst, t_3d *point1, t_3d *point2, float xans, float yans)
{
	int		x, y, p, inc;

	x = point1->x;
	y = point1->y;
	p = 2 * yans - xans;
	if (y < (int)point2->y)
		inc = 1;
	else
		inc = -1;
	while (x < (int)point2->x)
	{
		mlx_pixel_put(lst->mlx, lst->win, x, y, 0xFFFFFF);
		if (p < 0)
		{
			p += 2 * yans;
		}
		else
		{
			y += inc;
			p += 2 * (yans - xans);
		}
		x++;
	}
}

void 	get_DA(t_mlx *lst, t_3d *point1, t_3d *point2)
{
	float		xans, yans;

	xans = fabs(point2->x - point1->x);
	yans = fabs(point2->y - point1->y);
	if (xans > yans)
	{
		if (point1->x > point2->x)
			draw_x(lst, point2, point1, xans, yans);
		else
			draw_x(lst, point1, point2, xans, yans);
	}
	else
	{
		if (point1->y > point2->y)
			draw_y(lst, point2, point1, xans, yans);
		else
			draw_y(lst, point1, point2, xans, yans);
	}
}

void    check_for_line(t_mlx *lst, unsigned int i, unsigned int j)
{
	if (i + 1 < lst->h)
	{
		get_DA(lst, &lst->board[i][j].screen, &lst->board[i + 1][j].screen);
	}
	if (j + 1 < lst->l)
	{
		get_DA(lst, &lst->board[i][j].screen, &lst->board[i][j + 1].screen);
	}
}
