/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_path_expand.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/28 10:46:43 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/29 18:24:03 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_reverse(char dest[PATH_MAX + 1], char *addition)
{
	int i;

	i = 0;
	while (i < PATH_MAX && addition[i] != '\0')
	{
		dest[i] = addition[i];
		i++;
	}
	dest[i] = '\0';
	return (0);
}

int			ft_path_expand(char dest[PATH_MAX + 1], char path[PATH_MAX + 1],\
						char *addition, t_options options)
{
	int i;
	int j;

	j = 0;
	i = ft_strlen(path);
	ft_strcpy(dest, path);
	if (dest[i - 1] != '/')
	{
		dest[i] = '/';
		i++;
	}
	if ((options & e_args) == 0 && ft_strcmp(path, ".") == 0)
		return (ft_reverse(dest, addition));
	while (i < PATH_MAX && addition[j] != '\0')
	{
		dest[i] = addition[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	if (addition[j] != '\0')
		return (ft_print_error(ENAMETOOLONG, dest));
	return (0);
}
