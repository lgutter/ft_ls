/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_opt_error.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/20 21:28:49 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/20 21:36:31 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_opt_error(char option)
{
	ft_dprintf(2, "ft_ls: illegal option -- %c\n", option);
	ft_print_usage();
}
