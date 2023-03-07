/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_graphic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:37:30 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/07 10:47:50 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	print_line(t_data *data, t_point p2, t_point p1)
{
	double	delta_x;
	double	delta_y;
	int		pixels;
	double	pixel_x;
	double	pixel_y;

	delta_x = p2.x - p1.x;
	delta_y = p2.y - p1.y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = p1.x;
	pixel_y = p1.y;
	while (pixels--)
	{
		if ((int)pixel_y * data->width + (int)pixel_x < data->width * \
				data->height && \
				(int)pixel_x < data->width && (int)pixel_x > 0 && \
				(int)pixel_y < data->height && (int)pixel_y > 0)
			my_mlx_pixel_put(data, (int)pixel_x, (int)pixel_y, 0x0000FF00);
		pixel_x += delta_x;
		pixel_y += delta_y;
	}
}

void	print_lines(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->tab_len)
	{
		x = 0;
		while (x < data->line_len)
		{
			if ((x + 1) < data->line_len)
				print_line(data, data->tab_iso[y][x + 1], data->tab_iso[y][x]);
			if ((y + 1) < data->tab_len)
				print_line(data, data->tab_iso[y + 1][x], data->tab_iso[y][x]);
			x++;
		}
		y++;
	}
}

t_point	**init_tab_iso(t_data *data)
{
	t_point	**tab_iso;
	int		y;

	tab_iso = malloc(sizeof(t_point *) * data->tab_len);
	if (!tab_iso)
	{
		free_tab(data, data->tab_len);
		mlx_destroy_window(data->mlx, data->window);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		malloc_error();
	}
	y = -1;
	while (++y < data->tab_len)
	{
		tab_iso[y] = malloc(sizeof(t_point) * data->line_len);
		if (!tab_iso[y])
			free_mlx_tabs(data, y);
	}
	return (tab_iso);
}

void	project_iso(t_data *data)
{
	int		x;
	int		y;

	y = -1;
	while (++y < data->tab_len)
	{
		x = -1;
		while (++x < data->line_len)
		{
			data->tab_iso[y][x].x = data->x_offset + (data->zoom * (x - y)) \
				/ sqrt(2);
			data->tab_iso[y][x].y = data->y_offset - (data->tab[y][x] * \
			(data->zoom / data->altitude)) + (data->zoom * (x + y)) / sqrt(6);
		}
	}
}
