/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_error.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 10:43:57 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/03 15:06:42 by ivan-tey      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_print_error(int errnumber, char *errstr)
{
	g_exit_code = 1;
	if (errnumber == EACCES)
		errstr = ft_find_name_pointer(errstr);
	ft_dprintf(2, "ft_ls: %s: %s\n", errstr, strerror(errnumber));
	return (-1);
}
