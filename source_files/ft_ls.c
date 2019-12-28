/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/16 11:53:01 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/28 10:28:13 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ls(int filecount, char **filenames, t_options options)
{
	t_file_info		*current;
	int				i;

	i = 0;
	current = NULL;
	while (i < filecount)
	{
		ft_stats_to_list(filenames[i], &current);
		i++;
	}
	ft_sort_list(&current, options);
	ft_print_files_info(current, options);
	while (current != NULL)
	{
		if (S_ISDIR(current->lstats.st_mode))
		{
			if (filecount > 1)
				ft_printf("\n%s:\n", current->path);
			ft_rec_dir(current->path, options);
		}
		current = current->next;
	}
	return (0);
}
