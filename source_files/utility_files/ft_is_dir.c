/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_dir.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/29 17:46:36 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/03 15:00:07 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	check_open_dir(char *filename)
{
	DIR		*dirp;

	dirp = opendir(filename);
	if (dirp != NULL)
	{
		closedir(dirp);
		return (1);
	}
	return (0);
}

int			ft_is_dir(char *filename, t_options options)
{
	char	buf[PATH_MAX];

	if (readlink(filename, buf, PATH_MAX) > 0)
	{
		if ((options & e_opt_l) == 0 && (options & e_args) == 0)
		{
			if (check_open_dir(filename) == 1)
				return (1);
		}
		return (0);
	}
	else if (errno == EINVAL)
	{
		if (check_open_dir(filename) == 1)
			return (1);
		else if (errno == EACCES)
			return (1);
		else if (errno == ENOTDIR)
			return (0);
	}
	return (0);
}
