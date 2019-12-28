/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_rec_dir.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 12:35:11 by ivan-tey       #+#    #+#                */
/*   Updated: 2019/12/28 19:07:08 by ivan-tey      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_print_cur_dir(t_file_info *item)
{
	int		i;
	char	directory[PATH_MAX + 1];

	i = ((int)item->name_pointer - (int)item->path - 1);
	ft_strcpy(directory, item->path);
	directory[i] = '\0';
	ft_printf("\n%s:\n", directory);
}

static int		ft_check_rec(t_file_info *current, t_options options)
{
	if (!(S_ISDIR(current->lstats.st_mode)))
	{
		return (-1);
	}
	else if ((options & e_opt_R) == 0)
	{
		return (-1);
	}
	else if ((options & e_opt_a) == 0 && (current->name_pointer[0] == '.'))
	{
		return (-1);
	}
	else if (ft_strcmp(current->name_pointer, ".") == 0)
	{
		return (-1);
	}
	else if (ft_strcmp(current->name_pointer, "..") == 0)
	{
		return (-1);
	}
	else
	{
		return (1);
	}
}

static int		ft_print_dir(char dirname[PATH_MAX + 1], t_options *options,\
							t_file_info **list_start)
{
	DIR				*dir;
	struct dirent	*direntry;
	char			file[PATH_MAX + 1];

	dir = opendir(dirname);
	if (dir == NULL && ft_print_error(errno, dirname))
		return (-1);
	direntry = readdir(dir);
	while (direntry != NULL)
	{
		if (ft_path_expand(file, dirname, direntry->d_name, *options) == -1)
			return (-1);
		ft_stats_to_list(file, list_start);
		direntry = readdir(dir);
	}
	closedir(dir);
	ft_sort_list(list_start, *options);
	if ((*options & e_args) != 0)
		ft_print_cur_dir(*list_start);
	*options |= e_args;
	ft_print_files_info(*list_start, *options);
	return (0);
}

void			ft_rec_dir(char dirname[PATH_MAX + 1], t_options options)
{
	DIR				*dirp;
	t_file_info		*dir_list;
	char			next_dir[PATH_MAX + 1];

	dir_list = NULL;
	dirp = opendir(dirname);
	if (dirp == NULL)
	{
		ft_print_error(errno, dirname);
		return ;
	}
	if (ft_print_dir(dirname, &options, &dir_list) == -1)
		return ;
	while (dir_list != NULL)
	{
		if (ft_check_rec(dir_list, options) == 1)
		{
			if (ft_path_expand(next_dir, dirname, dir_list->name_pointer,\
								options) == -1)
				return ;
			ft_rec_dir(next_dir, options);
		}
		dir_list = dir_list->next;
	}
}
