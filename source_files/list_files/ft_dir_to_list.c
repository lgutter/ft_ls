/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dir_to_list.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/16 12:26:08 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/20 12:08:12 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_dir_to_list(char *dirname, t_options options)
{
	DIR				*dir;
	struct dirent	*direntry;

	dir = opendir(dirname);
	if (dir != NULL)
	{
		direntry = readdir(dir);
		while (direntry != NULL)
		{
			if (((options & e_opt_a) != 0) ||\
				(strcmp(direntry->d_name, ".") != 0 &&\
				strcmp(direntry->d_name, "..") != 0))
				ft_printf("%s\n", direntry->d_name);
			direntry = readdir(dir);
		}
		return (0);
	}
	ft_print_error(errno, dirname);
	return (-1);
}
