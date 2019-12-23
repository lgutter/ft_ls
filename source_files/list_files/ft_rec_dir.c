/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_rec_dir.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 12:35:11 by ivan-tey       #+#    #+#                */
/*   Updated: 2019/12/23 15:49:11 by ivan-tey      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_print_dir(char *dirname, t_options options)
{
	DIR				*dir;
	struct dirent	*direntry;
	t_file_info		*current;
	static int		i;

	current = NULL;
	dir = opendir(dirname);
	if (dir != NULL)
	{
		if (i != 0)
			ft_printf("\n%s:\n", dirname);
		direntry = readdir(dir);
		while (direntry != NULL)
		{
			if (dirname[ft_strlen(dirname) - 1] != '/')
					dirname = ft_strjoin(dirname, "/");
			ft_stats_to_list\
				(ft_strjoin(dirname, direntry->d_name), &current);
			if (((options & e_opt_a) != 0) ||\
				(direntry->d_name[0] != '.'))
				ft_printf("%s\n", direntry->d_name);
			direntry = readdir(dir);
		}
		ft_sort_list(&current, options);
		closedir(dir);
	}
	i = 1;
}

void			ft_rec_dir(char *dirname, t_options options)
{
	DIR				*dir;
	struct dirent	*direntry;

	ft_print_dir(dirname, options);
	dir = opendir(dirname);
	if (dir != NULL)
	{
		direntry = readdir(dir);
		while (direntry != NULL)
		{
			if (direntry->d_type == DT_DIR &&\
				((options & e_opt_R) != 0 &&\
				((options & e_opt_a) != 0 ||\
				(direntry->d_name[0] != '.')) &&\
				(strcmp(direntry->d_name, ".") != 0 &&\
				strcmp(direntry->d_name, "..") != 0)))
			{
				if (dirname[ft_strlen(dirname) - 1] != '/')
					dirname = ft_strjoin(dirname, "/");
				ft_rec_dir(ft_strjoin(dirname, direntry->d_name), options);
			}
			direntry = readdir(dir);
		}
		closedir(dir);
	}
}
