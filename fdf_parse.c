/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:09:03 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/07 10:48:15 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_lines(char *str)
{
	unsigned int	i;
	unsigned int	u;

	i = 0;
	u = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == ' ')
			i++;
		else if (ft_isdigit(str[i]) || str[i] == '-')
		{
			if (str[i] == '-')
				i++;
			while (ft_isdigit(str[i]))
				i++;
			u++;
		}
		else
			return (-1);
	}
	return (u);
}

void	check_valid_file(int fd, t_data *data)
{
	char	*str;
	int		len;
	int		n_line;

	str = get_next_line(fd);
	if (!str || str[0] == '\n')
		parse_error();
	len = count_lines(str);
	n_line = 1;
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		if (!str)
			break ;
		if (len != count_lines(str))
			parse_error();
		n_line++;
	}
	free(str);
	data->tab_len = n_line;
	data->line_len = len;
}

void	fill_line(t_data *data, char *str, int tab_len, int fd)
{
	unsigned int	i;
	unsigned int	u;
	unsigned int	tmp;
	char			*sub;

	i = 0;
	u = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == ' ')
			i++;
		else if (ft_isdigit(str[i]) || str[i] == '-')
		{
			tmp = i;
			if (str[i] == '-')
				i++;
			while (ft_isdigit(str[i]))
				i++;
			sub = ft_substr(str, tmp, (i - tmp));
			if (!sub)
				malloc_error_free(data, fd, str);
			data->tab[tab_len][u++] = ft_atoi(sub);
			free(sub);
		}
	}
}

void	fill_tab(t_data *data, int fd)
{
	char	*str;
	int		tab_len;

	str = get_next_line(fd);
	if (!str)
	{
		close(fd);
		free_tab(data, data->tab_len);
		parse_error();
	}
	fill_line(data, str, 0, fd);
	tab_len = 1;
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		if (!str)
			break ;
		fill_line(data, str, tab_len, fd);
		tab_len++;
	}
	free(str);
}

void	init_tab(int fd, t_data *data)
{
	int		i;

	check_valid_file(fd, data);
	data->tab = malloc(sizeof(int *) * data->tab_len);
	if (!data->tab)
	{
		close(fd);
		malloc_error();
	}
	i = 0;
	while (i < data->tab_len)
	{
		data->tab[i] = malloc(sizeof(int) * data->line_len);
		if (!data->tab[i])
		{
			close(fd);
			free_tab(data, i);
			malloc_error();
		}
		i++;
	}
}
