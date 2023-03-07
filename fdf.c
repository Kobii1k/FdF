/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:16:03 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/07 10:20:48 by mgagne           ###   ########.fr       */
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
	close(fd);
}

void	init_mlx(t_data *data)
{
	data->width = 1920;
	data->height = 1080;
	data->mlx = mlx_init();
	if (!(data->mlx))
		free_tab(data, data->tab_len);
	data->window = mlx_new_window(data->mlx, data->width, data->height, "FdF");
	if (!(data->window))
	{
		free_tab(data, data->tab_len);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	fit_to_window(data);
	data->tab_iso = init_tab_iso(data);
	update_map(data);
	mlx_hook(data->window, 2, 1L << 0, key_hook, data);
	mlx_hook(data->window, ON_DESTROY, 0, close_win, data);
	mlx_loop(data->mlx);
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
