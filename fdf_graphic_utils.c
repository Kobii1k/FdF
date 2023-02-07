/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_graphic_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:38:48 by mgagne            #+#    #+#             */
/*   Updated: 2023/02/07 11:22:32 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_win(t_data *data)
{
	free_tab(data, data->tab_len);
	mlx_destroy_window(data->mlx, data->window);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_win(data);
	return (0);
}

void	fit_zoom(t_data *data)
{
	int	highest;

	if (data->tab_len > data->line_len)
		highest = data->tab_len;
	else
		highest = data->line_len;
	if (highest > 350)
		data->zoom = 1;
	if (highest > 300)
		data->zoom = 3;
	if (highest > 200)
		data->zoom = 5;
	if (highest <= 200)
		data->zoom = 7;
	if (highest <= 100)
		data->zoom = 9;
	if (highest <= 50)
		data->zoom = 18;
	if (highest <= 25)
		data->zoom = 25;
	if (highest <= 20)
		data->zoom = 30;
	if (highest <= 10)
		data->zoom = 40;
}

void	fit_to_window(t_data *data)
{
	int	x;
	int	y;
	int	x_center;
	int	y_center;

	fit_zoom(data);
	x = data->line_len / 2;
	y = data->tab_len / 2;
	x_center = (data->zoom * (x - y)) / sqrt(2);
	y_center = data->tab[y][x] + (data->zoom * (x + y)) / sqrt(6);
	if (y_center % 2 == 1)
		y_center -= data->zoom;
	data->x_offset = data->width / 2 - x_center;
	data->y_offset = data->height / 2 - y_center;
}
