/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_dir.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/29 17:46:36 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/30 09:55:59 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_is_dir(char *filename)
{
	DIR		*dirp;
	char	buf[PATH_MAX];

	if (readlink(filename, buf, PATH_MAX) > 0)
		return (0);
	else if (errno == EINVAL)
	{
		dirp = opendir(filename);
		if (dirp != NULL)
		{
			closedir(dirp);
			return (1);
		}
		else if (errno == EACCES)
		{
			return (1);
		}
		else if (errno == ENOTDIR)
		{
			return (0);
		}
	}
	return (0);
}
