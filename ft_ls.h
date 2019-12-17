/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 11:33:09 by ivan-tey       #+#    #+#                */
/*   Updated: 2019/12/17 11:10:28 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>
# include <limits.h>
# include "ft_printf.h"

enum						e_options
{
	e_opt_l = 1 << 0,
	e_opt_R = 1 << 1,
	e_opt_a = 1 << 2,
	e_opt_r = 1 << 3,
	e_opt_t = 1 << 4,
};

typedef unsigned long long	t_options;

/*
**	Core functions
*/

int				main(int argc, char **argv);

/*
** Find functions
*/

int				ft_find_options(int argc, char **argv, t_options *options);

/*
**	Utility functions
*/

void			ft_print_error(char *errdex, char *errstr);

#endif
