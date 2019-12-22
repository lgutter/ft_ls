/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_time_sort.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/22 13:25:14 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/22 14:07:14 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file_info	*ft_swap_start_list(t_file_info **list_start)
{
	t_file_info	*current;

	current = (*list_start)->next;
	if (current->lstats.st_mtimespec.tv_sec >\
	(*list_start)->lstats.st_mtimespec.tv_sec)
	{
		(*list_start)->next = current->next;
		current->next = *list_start;
		*list_start = current;
	}
	return (*list_start);
}

void				ft_time_sort(t_file_info **list_start)
{
	t_file_info	*current;
	t_file_info	*previous;
	t_file_info	*future;

	current = (*list_start)->next;
	previous = ft_swap_start_list(list_start);
	future = current->next;
	while (current->next != NULL)
	{
		if (future->lstats.st_mtimespec.tv_sec >\
			current->lstats.st_mtimespec.tv_sec)
		{
			previous->next = future;
			current->next = future->next;
			future->next = current;
			previous = future;
			future = current->next;
		}
		else
		{
			previous = current;
			current = future;
			future = future->next;
		}
	}
}
