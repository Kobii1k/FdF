/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_graphic_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:38:48 by mgagne            #+#    #+#             */
/*   Updated: 2023/02/23 17:59:25 by mgagne           ###   ########.fr       */
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
	printf("%d");
	if (keycode == 65362)
	{
		//haut
	}
	if (keycode == 65364)
	{
		//bas
	}
	if (keycode == 65361)
	{
		//gauche
	}
	if (keycode == 65363)
	{
		//droite
	}
	if (keycode == 65307)
		close_win(data);
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
