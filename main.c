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
#include <stdio.h>

void		*error(char *msg)
{
	ft_putstr("Error: ");
	ft_putendl(msg);
	return (NULL);
}

unsigned int	count_ord(char *av)
{
	int				fd;
	char			*tmp;
	unsigned int	count;

	count = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return((int)error("failed to open file"));
	while(get_next_line(fd, &tmp))
		count++;
	close(fd);
	return (count);
}

vertex_t	*store_local(char **line, unsigned int y, unsigned int count)
{
	vertex_t		*array;
	vertex_t		tmp;
	unsigned int	x;

	x = 0;
	array = (vertex_t*)malloc(sizeof(vertex_t) * count);
	while (line[x])
	{
		tmp.Local.x = x;
		tmp.Local.y = y;
		tmp.Local.z = ft_atoi(line[x]);
		array[x] = tmp;
		x++;
	}
	return (array);
}

void		read_file(char *av, vertex_t **board, unsigned int count)
{
	int				fd, ret;
	unsigned int	i;
	char			*tmp;

	i = 0;
	fd = open(av, O_RDONLY);
	while((ret = get_next_line(fd, &tmp)))
	{
		board[i] = store_local(ft_strsplit(tmp, ' '), i, count);
		i++;
	}
	close(fd);
}

int			main(int argc, char **argv)
{
	vertex_t		**board;
	unsigned int	count;

	if (argc != 2)
		return((int)error("wronge number of input files"));
	if (!(count = count_ord(argv[1])))
		return (0);
	board = (vertex_t**)malloc(sizeof(vertex_t*) * count);
	read_file(argv[1], board, count);
	split_board(board, count);
	return (1);
}
