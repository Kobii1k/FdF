/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_graphic_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:38:48 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/03 15:16:02 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_win(t_data *data)
{
	free_tab(data, data->tab_len);
	free_tab_iso(data->tab_iso, data->tab_len);
	mlx_destroy_window(data->mlx, data->window);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	printf("%d\n\n", keycode);
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
	mlx_destroy_image(data->mlx, data->img);
	update_map(data);
	return (0);
}

void	update_map(t_data *data)
{
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->tab_iso = project_iso(data);
	print_lines(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}

void	fit_to_window(t_data *data)
{
	int	x;
	int	y;
	int	x_center;
	int	y_center;

	data->zoom = ((data->width + data->height) / 2)
		/ (data->line_len + data->tab_len);
	x = data->line_len / 2;
	y = data->tab_len / 2;
	x_center = (data->zoom * (x - y)) / sqrt(2);
	y_center = data->tab[y][x] + (data->zoom * (x + y)) / sqrt(6);
	if (y_center % 2 == 1)
		y_center -= data->zoom;
	data->x_offset = (data->width / 2 - x_center) + data->x_translate;
	data->y_offset = (data->height / 2 - y_center) + data->y_translate;
}
