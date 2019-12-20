/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_error.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 10:43:57 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/20 21:56:36 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_error(int errnumber, char *errstr)
{
	if (errnumber == EACCES)
		errstr = ft_find_name_pointer(errstr);
	ft_dprintf(2, "ft_ls: %s: %s\n", errstr, strerror(errnumber));
}
