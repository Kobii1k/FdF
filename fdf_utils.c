/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:20:24 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/07 10:26:21 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_format(char *str)
{
	unsigned int	i;
	unsigned int	j;
	char			*cmp;

	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	if (!str[i])
		return (-1);
	cmp = ".fdf";
	j = 0;
	while (str[i])
	{
		if (str[i++] != cmp[j++])
			return (-1);
	}
	if (j <= 3)
		return (-1);
	return (0);
}

void	free_tab(t_data *data, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(data->tab[i]);
		i++;
	}
	free(data->tab);
}

void	free_tab_iso(t_point **tab_iso, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(tab_iso[i]);
		i++;
	}
	free(tab_iso);
}

void	malloc_error_free(t_data *data, int fd, char *str)
{
	close(fd);
	free_tab(data, data->tab_len);
	free(str);
	malloc_error();
}
