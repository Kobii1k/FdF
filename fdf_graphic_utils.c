/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_graphic_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:38:48 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/02 13:40:23 by mgagne           ###   ########.fr       */
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
void	handle_translation(int keycode, t_data *data)
{
	if (keycode == 65362)
		data->y_translate -= 40;
	if (keycode == 65364)
		data->y_translate += 40;
	if (keycode == 65361)
		data->x_translate -= 40;
	if (keycode == 65363)
		data->x_translate += 40;
	mlx_destroy_image(data->mlx, data->img);
}

void	handle_zoom(int keycode, t_data *data)
{
	if (keycode == 65453)
		data->zoom *= 0.1;
	if (keycode == 65451)
		data->zoom *= 0.1;
	mlx_destroy_image(data->mlx, data->img);
}
int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_win(data);
	if (keycode == 65362 || keycode == 65364
		|| keycode == 65361 || keycode == 65363)
	{
		handle_translation(keycode, data);
	}
	if (keycode == 65453 || keycode == 65451)
	{
		handle_zoom(keycode, data);
	}
	ft_update_map(data);
	return (0);
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
