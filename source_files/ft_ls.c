/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/16 11:53:01 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/28 16:48:47 by lgutter       ########   odam.nl         */
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
		if ((options & e_args) != 0)
			options -= e_args;
		if (S_ISDIR(current->lstats.st_mode))
		{
			ft_rec_dir(current->path, options);
		}
		current = current->next;
	}
	return (0);
}
