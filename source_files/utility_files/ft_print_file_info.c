/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_file_info.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 12:18:01 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/23 17:16:59 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_width	*ft_init_width(t_file_info *list_start)
{
	t_width		*width;
	t_file_info	*l_item;

	l_item = list_start;
	width = (t_width *)ft_memalloc(sizeof(t_width));
	if (width == NULL)
		return (NULL);
	while (l_item != NULL)
	{
		ft_conv_info_to_str(list_start);
		width->links = ft_strlonger(width->links, l_item->links);
		width->user = ft_strlonger(width->user, l_item->u_name);
		width->group = ft_strlonger(width->group, l_item->g_name);
		width->size = ft_strlonger(width->size, l_item->size);
		width->date = ft_strlonger(width->date, l_item->date);
	}
}

static void		ft_print_info(t_file_info *item, t_width *width)
{
	ft_printf("%-11s ", item->mode);
	ft_printf("%*s ", width->links, item->links);
	ft_printf("%*s ", width->user, item->u_name);
	ft_printf("%*s ", width->group, item->g_name);
	ft_printf("%*s ", width->size, item->size);
	ft_printf("%3s ", item->month);
	ft_printf("%*s ", width->date, item->date);
	ft_printf("%*s ", width->tiye, item->tiye);
	ft_printf("%*s ", item->name_pointer);
}

void			ft_print_files_info(t_file_info *list_start, t_options options)
{
	t_width		*width;
	t_file_info	*current;

	current = list_start;
	if ((options & e_opt_l) != 0)
		width = ft_init_width(list_start);
	while (current != NULL)
	{
		if ((options & e_opt_a) != 0 || current->name_pointer[0] != '.')
		{
			if ((options & e_opt_l) != 0)
				ft_print_info(current, width);
			else
				ft_printf("%s\n", current->name_pointer);
		}
		current = current->next;
	}
}
