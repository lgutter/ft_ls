/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_file_info.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 12:18:01 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/03 14:50:46 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_width	*ft_init_width(t_file_info *list_start, t_options options)
{
	t_width		*width;
	t_file_info	*l_item;

	l_item = list_start;
	width = (t_width *)ft_memalloc(sizeof(t_width));
	if (width == NULL)
		return (NULL);
	width->blocks = 0;
	while (l_item != NULL)
	{
		ft_conv_info_to_str(list_start);
		width->links = ft_strlonger(width->links, l_item->links);
		width->user = ft_strlonger(width->user, l_item->u_name);
		width->group = ft_strlonger(width->group, l_item->g_name);
		width->size = ft_strlonger(width->size, l_item->size);
		width->date = ft_strlonger(width->date, l_item->date);
		if ((options & e_args) == 0 || (options & e_opt_a) != 0 ||\
			l_item->name_pointer[0] != '.')
			width->blocks += l_item->lstats.st_blocks;
		l_item = l_item->next;
	}
	return (width);
}

static void		ft_print_info(t_file_info *item, t_width *width,\
								t_options options)
{
	if (S_ISLNK(item->lstats.st_mode))
	{
		if (readlink(item->path, item->link_path, PATH_MAX) < 0)
		{
			ft_dprintf(2, "\n");
			ft_print_error(errno, item->name_pointer);
		}
	}
	ft_printf("%-11s ", item->mode);
	ft_printf("%*s ", width->links, item->links);
	ft_printf("%-*s  ", width->user, item->u_name);
	ft_printf("%-*s  ", width->group, item->g_name);
	ft_printf("%*s ", width->size, item->size);
	ft_printf("%3s ", item->month);
	ft_printf("%*s ", width->date, item->date);
	ft_printf("%5s ", item->tiye);
	if ((options & e_args) == 0)
		ft_printf("%s", item->path);
	else
		ft_printf("%s", item->name_pointer);
	if (S_ISLNK(item->lstats.st_mode) && item->link_path[0] != '\0')
		ft_printf(" -> %s", item->link_path);
	ft_printf("\n");
}

static int		ft_check_print(t_file_info *l_item, t_options options)
{
	if ((options & e_args) == 0 && ft_is_dir(l_item->path, options) == 0)
	{
		return (1);
	}
	else if ((options & e_args) != 0)
	{
		if ((options & e_opt_a) != 0 || l_item->name_pointer[0] != '.')
		{
			return (1);
		}
	}
	return (0);
}

void			ft_print_files_info(t_file_info *list_start, t_options options)
{
	t_width		*width;
	t_file_info	*current;

	current = list_start;
	width = NULL;
	if ((options & e_opt_l) != 0)
		width = ft_init_width(list_start, options);
	if ((options & e_opt_l) != 0 && (options & e_args) != 0)
		ft_printf("total %lu\n", width->blocks);
	while (current != NULL)
	{
		if (ft_check_print(current, options) == 1)
		{
			if ((options & e_opt_l) != 0)
				ft_print_info(current, width, options);
			else if ((options & e_args) == 0)
				ft_printf("%s\n", current->path);
			else
				ft_printf("%s\n", current->name_pointer);
		}
		current = current->next;
	}
	if (width != NULL)
		free(width);
}
