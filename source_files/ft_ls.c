/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/16 11:53:01 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/17 19:35:18 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ls(int filecount, char **filenames, t_options options)
{
	t_file_info		*list_start;
	t_file_info		*current;
	int				i;

	i = 0;
	list_start = NULL;
	(void)options;
	while (i < filecount)
	{
		current = ft_stats_to_list(filenames[i], &list_start);
		if (current == NULL)
			ft_print_error("notfound", filenames[i]);
		else if (S_ISDIR(current->stats.st_mode))
			ft_dir_to_list(current->path, options);
		else
			ft_printf("%s\n", current->path);
		i++;
	}
	return (0);
}
