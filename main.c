/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 14:45:15 by lhurt             #+#    #+#             */
/*   Updated: 2016/10/21 14:45:25 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*error(char *msg)
{
	ft_putstr("Error: ");
	ft_putendl(msg);
	return (NULL);
}


void	print_board(char **board, unsigned int size)
{
	unsigned int j;

	j = 0;
	while (j < size)
	{
		ft_putendl(board[j]);
		j++;
	}
}

int	my_key_funct(int keycode, t_mlx *lst)
{
	int		x;
	int		y;

	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 36)
	{
		y = 200;
		while (y < 300)
		{
			x = 200;
			while (x < 300)
			{
				mlx_pixel_put(lst->mlx, lst->win, x, y, 0xFF0000);
				x += 5 * 2;
			}
			y += 2 * 3 -2;
		}
	}
	return (0);
}

void	test_func(void)
{
	t_mlx	*new;
	int		x;
	int		y;

	new = malloc(sizeof(t_mlx));
	new->mlx = mlx_init();
	new->win = mlx_new_window(new->mlx, 400, 400, "mlx 42");
	y = 1;
	while (y < 400)
	{
		x = 1;
		while (x < 400)
		{
			mlx_pixel_put(new->mlx, new->win, x, y, 0x00FFFFFF);
			x += 2 + y;
		}
		y += 5 / 2;
	}
	mlx_key_hook(new->win, my_key_funct, new);
	mlx_loop(new->mlx);
}

int		count_ord(char *av)
{
	int				fd;
	char			*tmp;
	unsigned int	count;

	count = 0;
	fd = open(av, O_RDONLY);
	while(get_next_line(fd, &tmp))
		count++;
	close(fd);
	return (count);
}

int		read_file(char *av, char **board)
{
	int				fd;
	unsigned int	i;
	int				ret;
	char			*tmp;

	i = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return((int)error("failed to open file"));
	while((ret = get_next_line(fd, &tmp)))
	{
		board[i] = tmp;
		i++;
	}
	if (ret < 0)
		return((int)error("failed to get next line"));
	close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	char **board;

	if (argc != 2)
		return((int)error("wronge number of input files"));
	board = (char**)malloc(sizeof(char*) * count_ord(argv[1]));
	if (!read_file(argv[1], board))
		return (0);
	print_board(board, count_ord(argv[1]));
	return (1);
}
