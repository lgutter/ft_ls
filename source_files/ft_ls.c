/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/16 11:53:01 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/03 15:36:28 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_handle_list(t_file_info **list_start, t_options options, int fc)
{
	t_file_info *current;

	current = *list_start;
	while (current != NULL)
	{
		if ((options & e_args) != 0)
			options -= e_args;
		if (fc > 1)
			options |= e_args;
		if (ft_is_dir(current->path, options) == 1)
			ft_rec_dir(current->path, options);
		current = current->next;
	}
}

/*
**	Declaration of the global variable g_exit_code
*/

int			g_exit_code;

int			ft_ls(int filecount, char **filenames, t_options options)
{
	t_file_info		*current;
	int				i;

	i = 0;
	g_exit_code = 0;
	current = NULL;
	while (i < filecount)
	{
		ft_stats_to_list(filenames[i], &current, options);
		i++;
	}
	if (current != NULL)
		ft_sort_list(&current, options);
	ft_print_files_info(current, options);
	ft_handle_list(&current, options, filecount);
	if (current != NULL)
		ft_free_list(&current);
	return (g_exit_code);
}
