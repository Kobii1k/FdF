/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_graphic_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:38:48 by mgagne            #+#    #+#             */
/*   Updated: 2023/02/24 11:59:47 by mgagne           ###   ########.fr       */
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

// void	translate(t_data *data, int x_add, int y_add)
// {
// 	/*
// 	int x;
// 	int y;

// 	y = 0;
// 	while (y < data->tab_len)
// 	{
// 		x = 0;
// 		while (x < data->line_len)
// 		{
// 			data->tab_iso[y][x].x += 40;
// 			data->tab_iso[y][x].y += 40;
// 			x++;
// 		}
// 		y++;
// 	}
// 	print_lines(data);
// 	*/

// 	//faire une nouvelle image avec le nvx tab
// 	//suppr lancienne
// 	//ajoute la nouvelle image a mlx
// 	//reload
// }

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65362)
		data->x_translate += 40;
	if (keycode == 65364)
		data->x_translate -= 40;
	if (keycode == 65361)
		data->y_translate -= 40;
	if (keycode == 65363)
		data->y_translate += 40;
	if (keycode == 65307)
		close_win(data);
	mlx_destroy_image(data->mlx, data->img.img);
	ft_update_map(data);
	return (0);
}

void	fit_to_window(t_data *data)
{
	int	x;
	int	y;
	int	x_center;
	int	y_center;

	data->zoom = ((data->width + data->height) / 2) / (data->line_len + data->tab_len);
	x = data->line_len / 2;
	y = data->tab_len / 2;
	x_center = (data->zoom * (x - y)) / sqrt(2);
	y_center = data->tab[y][x] + (data->zoom * (x + y)) / sqrt(6);
	if (y_center % 2 == 1)
		y_center -= data->zoom;
	data->x_offset = data->width / 2 - x_center;
	data->y_offset = data->height / 2 - y_center;
}
