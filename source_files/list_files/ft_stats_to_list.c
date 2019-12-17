/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stats_to_list.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 11:31:46 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/17 15:48:25 by lgutter       ########   odam.nl         */
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

static char			*find_name_pointer(char path[PATH_MAX + 1])
{
	char *name_pointer;

	name_pointer = &(path[0]);
	while (*name_pointer != '\0' && name_pointer != &(path[PATH_MAX]))
		name_pointer++;
	while (*name_pointer != '/' && name_pointer != &(path[0]))
		name_pointer--;
	return (name_pointer + (name_pointer[0] == '/'));
}

static int			fetch_names(t_file_info *new)
{
	struct passwd	*p_info;
	struct group	*g_info;

	p_info = getpwuid(new->stats.st_uid);
	g_info = getgrgid(new->stats.st_gid);
	if (p_info == NULL || g_info == NULL)
		return (-1);
	if (ft_strncpy(&(new->u_name[0]), p_info->pw_name, NAME_MAX) == NULL ||\
	ft_strncpy(&(new->g_name[0]), g_info->gr_name, NAME_MAX) == NULL)
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
		new->name_pointer = find_name_pointer(new->path);
		if (lstat(filename, &(new->stats)) != 0 || fetch_names(new) != 0)
			return ((t_file_info *)ft_error_free((void **)new_pointer));
		if (S_ISLNK(new->stats.st_mode))
			return (check_link(new_pointer));
	}
	return (new);
}
