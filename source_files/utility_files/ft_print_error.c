/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_error.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 10:43:57 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/13 11:34:12 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_error(char *errdex, char *errstr)
{
	char *usage;

	usage = "usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]";
	if (ft_strcmp(errdex, "notfound") == 0)
	{
		ft_dprintf(2, "ls: %s: No such file or directory\n", errstr);
	}
	else if (ft_strcmp(errdex, "option") == 0)
	{
		ft_dprintf(2, "ls: illegal option -- %c\n", *errstr);
	}
	else
	{
		ft_dprintf(2, "%s\n", usage);
	}
}
