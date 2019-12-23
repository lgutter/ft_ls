/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_conv_info_to_str.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 17:05:02 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/23 17:20:18 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_conv_mode_str(t_file_info *l_item)
{
	THIS FUNCTION WILL CONVERT
	l_item->lstats.st_mode
	TO A STRING AND PUT IT IN
	l_item->mode
}

static void	ft_conv_time_str(t_file_info *l_item)
{
	THIS FUNCTION WILL CONVERT
	l_item->lstats.st_mtimespec.tv_sec
	TO A MONTH, DATE AND TIME / YEAR AND PUT THEM IN:
	l_item->month
	l_item->date
	l_item->tiye
}

void		ft_conv_info_to_str(t_file_info *l_item)
{
	char *str;

	while (l_item != NULL)
	{
		ft_conv_mode_str(l_item);
		str = ft_itoa(l_item->lstats.st_nlink);
		ft_strncpy(l_item->links, str, 8);
		free(str);
		str = ft_itoa(l_item->lstats.st_size);
		ft_strncpy(l_item->size, str, 8);
		free(str);
		ft_conv_time_str(l_item);
		l_item = l_item->next;
	}
}
