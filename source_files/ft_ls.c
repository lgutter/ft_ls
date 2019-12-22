/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/16 11:53:01 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/22 15:51:25 by lgutter       ########   odam.nl         */
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
	while (current != NULL)
	{
		if (S_ISDIR(current->lstats.st_mode))
		{
			if (filecount > 1)
				ft_printf("\n%s:\n", current->path);
			ft_dir_to_list(current->path, options);
		}
		else
			ft_printf("%s\n", current->path);
		current = current->next;
	}
	return (0);
}
