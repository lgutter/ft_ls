/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_rec_dir.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 12:35:11 by ivan-tey       #+#    #+#                */
/*   Updated: 2020/01/03 14:50:44 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_print_cur_dir(char dirname[PATH_MAX + 1])
{
	int		i;

	i = ft_strlen(dirname);
	i--;
	if (dirname[i] == '/')
		dirname[i] = '\0';
	ft_printf("\n%s:\n", dirname);
}

static int		ft_check_rec(t_file_info *current, t_options options)
{
	if (ft_is_dir(current->path, options) == 0)
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
	*options |= e_args;
	while (direntry != NULL)
	{
		if (ft_path_expand(file, dirname, direntry->d_name, *options) == -1)
			return (-1);
		if (ft_check_need_stats(*options, direntry->d_name[0], 'a'))
			ft_stats_to_list(file, list_start, *options);
		direntry = readdir(dir);
	}
	closedir(dir);
	if (*list_start != NULL)
	{
		ft_sort_list(list_start, *options);
		ft_print_files_info(*list_start, *options);
	}
	return (0);
}

static int		ft_handle_dir_list(t_file_info *dir_list, t_options options,\
									char dirname[PATH_MAX + 1])
{
	char			next_dir[PATH_MAX + 1];

	if ((options & e_opt_R) != 0)
	{
		while (dir_list != NULL)
		{
			if (ft_check_rec(dir_list, options) == 1)
			{
				if (ft_path_expand(next_dir, dirname, dir_list->name_pointer,\
									options) == -1)
					return (-1);
				ft_rec_dir(next_dir, options);
			}
			dir_list = dir_list->next;
		}
	}
	return (0);
}

int				ft_rec_dir(char dirname[PATH_MAX + 1], t_options options)
{
	t_file_info		*dir_list;

	dir_list = NULL;
	if ((options & e_args) != 0)
		ft_print_cur_dir(dirname);
	if (ft_print_dir(dirname, &options, &dir_list) == -1)
		return (-1);
	if (ft_handle_dir_list(dir_list, options, dirname) == -1)
		return (-1);
	if (dir_list != NULL)
		ft_free_list(&dir_list);
	return (0);
}
