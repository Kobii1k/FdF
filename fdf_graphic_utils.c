/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_graphic_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:38:48 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/06 18:58:33 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_win(t_data *data)
{
	free_tab(data, data->tab_len);
	free_tab_iso(data->tab_iso, data->tab_len);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_win(data);
	if (keycode == 65362)
		data->y_offset -= 40;
	if (keycode == 65364)
		data->y_offset += 40;
	if (keycode == 65361)
		data->x_offset -= 40;
	if (keycode == 65363)
		data->x_offset += 40;
	if (keycode == 65453)
		data->zoom *= 0.95;
	if (keycode == 65451)
		data->zoom *= 1.05;
	if (keycode == 114)
		fit_to_window(data);
	if (keycode == 109)
		data->altitude += 1;
	if (keycode == 110)
		data->altitude -= 1;
	mlx_destroy_image(data->mlx, data->img);
	update_map(data);
	return (0);
}

void	fit_to_window(t_data *data)
{
	int	x;
	int	y;
	int	x_center;
	int	y_center;

	data->altitude = 5;
	data->zoom = round(((data->width + data->height) / 2)
		/ (data->line_len + data->tab_len));
	x = data->line_len / 2;
	y = data->tab_len / 2;
	x_center = (data->zoom * (x - y)) / sqrt(2);
	y_center = data->tab[y][x] + (data->zoom * (x + y)) / sqrt(6);
	if (y_center % 2 == 1)
		y_center -= data->zoom;
	data->x_offset = (data->width / 2 - x_center);
	data->y_offset = (data->height / 2 - y_center);
}
