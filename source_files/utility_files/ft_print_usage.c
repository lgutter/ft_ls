/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_usage.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/20 21:29:23 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/20 21:30:20 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_usage(void)
{
	char *usage;

	usage = "usage: ft_ls [-Ralrt] [file ...]";
	ft_dprintf(2, "%s\n", usage);
}
