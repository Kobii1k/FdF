/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:16:03 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/02 11:33:20 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_struct(char *argv1, t_data *data)
{
	int		fd;

	fd = open(argv1, O_RDONLY);
	if (fd < 0 || read(fd, 0, 0) < 0)
	{
		close(fd);
		read_error();
	}
	init_tab(fd, data);
	close(fd);
	fd = open(argv1, O_RDONLY);
	if (fd < 0 || read(fd, 0, 0) < 0)
	{
		close(fd);
		free_tab(data, data->tab_len);
		read_error();
	}
	fill_tab(data, fd);
	data->x_translate = 0;
	data->y_translate = 0;
	close(fd);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		nb_arg_error();
	if (check_format(av[1]) == -1)
		arg_format_error();
	init_struct(av[1], &data);
	init_mlx(&data);
	return (0);
}
