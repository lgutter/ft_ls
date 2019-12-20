/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stats_to_list.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 11:31:46 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/20 12:47:49 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file_info	*init_list_item(t_file_info **list_start)
{
	t_file_info *new;

	if (*list_start == NULL)
	{
		new = (t_file_info *)ft_memalloc(sizeof(t_file_info));
		*list_start = new;
		return (new);
	}
	else
	{
		new = *list_start;
		while (new->next != NULL)
			new = new->next;
		new->next = (t_file_info *)ft_memalloc(sizeof(t_file_info));
		return (new->next);
	}
}

static int			fetch_names(t_file_info *new)
{
	struct passwd	*p_info;
	struct group	*g_info;

	p_info = getpwuid(new->stats.st_uid);
	if (p_info == NULL)
	{
		if (ft_strncpy(&(new->u_name[0]),\
			ft_itoa(new->stats.st_uid), NAME_MAX) == NULL)
			return (-1);
	}
	else if (ft_strncpy(&(new->u_name[0]), p_info->pw_name, NAME_MAX) == NULL)
		return (-1);
	g_info = getgrgid(new->stats.st_gid);
	if (g_info == NULL)
	{
		if (ft_strncpy(&(new->g_name[0]),\
			ft_itoa(new->stats.st_gid), NAME_MAX) == NULL)
			return (-1);
	}
	else if (ft_strncpy(&(new->g_name[0]), g_info->gr_name, NAME_MAX) == NULL)
		return (-1);
	return (0);
}

static t_file_info	*check_link(t_file_info **new_pointer)
{
	t_file_info *new;

	new = *new_pointer;
	if (readlink(new->path, new->link_path, PATH_MAX) < 0)
		return ((t_file_info *)ft_error_free((void **)new_pointer));
	return (new);
}

t_file_info			*ft_stats_to_list(char *filename, t_file_info **list_start)
{
	t_file_info	*new;
	t_file_info	**new_pointer;

	new = init_list_item(list_start);
	new_pointer = &new;
	if (new != NULL)
	{
		if (ft_strncpy(&(new->path[0]), filename, PATH_MAX) == NULL)
			return ((t_file_info *)ft_error_free((void **)new_pointer));
		new->name_pointer = ft_find_name_pointer(new->path);
		if (lstat(filename, &(new->stats)) != 0)
		{
			ft_print_error(errno, filename);
			return ((t_file_info *)ft_error_free((void **)new_pointer));
		}
		else if (fetch_names(new) != 0)
			return ((t_file_info *)ft_error_free((void **)new_pointer));
		if (S_ISLNK(new->stats.st_mode))
			return (check_link(new_pointer));
	}
	return (new);
}
