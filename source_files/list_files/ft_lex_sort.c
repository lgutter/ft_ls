/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lex_sort.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/22 13:25:14 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/22 14:06:54 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file_info	*ft_swap_start_list(t_file_info **list_start)
{
	t_file_info	*current;

	current = (*list_start)->next;
	if (strcmp((*list_start)->path, current->path) > 0)
	{
		(*list_start)->next = current->next;
		current->next = *list_start;
		return (current);
	}
	else
	{
		return (*list_start);
	}
}

void				ft_lex_sort(t_file_info **list_start)
{
	t_file_info	*current;
	t_file_info	*previous;
	t_file_info	*future;

	*list_start = ft_swap_start_list(list_start);
	current = (*list_start)->next;
	previous = *list_start;
	future = current->next;
	while (current->next != NULL)
	{
		if (strcmp(current->path, future->path) > 0)
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
