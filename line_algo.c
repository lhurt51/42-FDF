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

void 	draw_y(t_mlx *lst, _3D *point1, _3D *point2, float xans, float yans)
{
	int		x, y, p, end, inc, xend;

	x = point1->x;
	y = point1->y;
	xend = point2->x;
	end = point2->y;
	p = 2 * xans - yans;
	if (x < xend)
		inc = 1;
	else
		inc = -1;
	while (y < end)
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

void 	draw_x(t_mlx *lst, _3D *point1, _3D *point2, float xans, float yans)
{
	int		x, y, p, end, inc, yend;

	x = point1->x;
	y = point1->y;
	end = point2->x;
	yend = point2->y;
	p = 2 * yans - xans;
	if (y < yend)
		inc = 1;
	else
		inc = -1;
	while (x < end)
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

void 	get_DA(t_mlx *lst, _3D *point1, _3D *point2)
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
