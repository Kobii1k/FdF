/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:11:34 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/07 10:44:15 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "big_Libft/libft.h"
# include "mlx/mlx.h"

typedef struct s_point
{
	int	x;
	int	y;
}			t_point;

typedef struct s_data
{
	int		**tab;
	int		tab_len;
	int		line_len;

	t_point	**tab_iso;

	int		width;
	int		height;
	void	*mlx;
	void	*window;
	int		x_offset;
	int		y_offset;
	double	zoom;
	double	altitude;

	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

//fdf
void	init_struct(char *argv1, t_data *data);
void	init_mlx(t_data *data);

//fdf_utils
int		check_format(char *str);
void	free_tab(t_data *data, int index);
void	free_tab_iso(t_point **tab_iso, int index);
void	malloc_error_free(t_data *data, int fd, char *str);
void	free_2_tabs(t_data *data, t_point **tab_iso, int y);

//fdf_parse
int		count_lines(char *str);
void	check_valid_file(int fd, t_data *data);
void	fill_line(t_data *data, char *str, int tab_len, int fd);
void	fill_tab(t_data *data, int fd);
void	init_tab(int fd, t_data *data);

//fdf_graphic
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	print_line(t_data *data, t_point p2, t_point p1);
void	print_lines(t_data *data);
void	project_iso(t_data	*data);
t_point	**init_tab_iso(t_data *data);
int		update_map(t_data *data);

//fdf_graphic_utils
int		close_win(t_data *data);
int		key_hook(int keycode, t_data *data);
void	fit_to_window(t_data *data);
void	free_mlx_tabs(t_data *data, int y);

//fdf_error
void	parse_error(void);
void	malloc_error(void);
void	nb_arg_error(void);
void	arg_format_error(void);
void	read_error(void);

#endif
