/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:39:53 by mgagne            #+#    #+#             */
/*   Updated: 2023/03/03 16:50:51 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parse_error(void)
{
	write(2, "error : parsing or invalid file\n", 32);
	exit(EXIT_FAILURE);
	return ;
}

void	malloc_error(void)
{
	write(2, "error : malloc\n", 15);
	exit(EXIT_FAILURE);
	return ;
}

void	nb_arg_error(void)
{
	write(2, "error : program only takes 1 argument\n", 38);
	exit(EXIT_FAILURE);
	return ;
}

void	arg_format_error(void)
{
	write(2, "error : file must be \".fdf\" type\n", 33);
	exit(EXIT_FAILURE);
	return ;
}

void	read_error(void)
{
	write(2, "error : couldn't open/read from file\n", 37);
	exit(EXIT_FAILURE);
	return ;
}
