/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:39:53 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/04 12:22:04 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parse_error(void)
{
	ft_printfd(2, "%s", "error : parsing or invalid file\n");
	exit(EXIT_FAILURE);
	return ;
}

void	malloc_error(void)
{
	ft_printfd(2, "%s", "error : malloc\n");
	exit(EXIT_FAILURE);
	return ;
}

void	nb_arg_error(void)
{
	ft_printfd(2, "%s", "error : program only takes 1 argument\n");
	exit(EXIT_FAILURE);
	return ;
}

void	arg_format_error(void)
{
	ft_printfd(2, "%s", "error : file must be \".fdf\" type\n");
	exit(EXIT_FAILURE);
	return ;
}

void	read_error(void)
{
	ft_printfd(2, "%s", "error : couldn't open/read from file\n");
	exit(EXIT_FAILURE);
	return ;
}
