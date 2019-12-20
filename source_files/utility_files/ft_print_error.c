/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_error.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 10:43:57 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/20 13:17:55 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_error(int errnumber, char *errstr)
{
	char *usage;

	usage = "usage: ft_ls [-Ralrt] [file ...]";
	if (errnumber == ENOENT)
		ft_dprintf(2, "ft_ls: %s: No such file or directory\n", errstr);
	else if (errnumber == EILLOPT)
		ft_dprintf(2, "ft_ls: illegal option -- %c\n%s\n", *errstr, usage);
	else if (errnumber == EACCES)
	{
		errstr = ft_find_name_pointer(errstr);
		ft_dprintf(2, "ft_ls: %s: Permission denied\n", errstr);
	}
	else if (errnumber == EUSAGE)
		ft_dprintf(2, "%s\n", usage);
	else
		ft_dprintf(2, "ft_ls: %i: Unknown errno\n", errnumber);
}
