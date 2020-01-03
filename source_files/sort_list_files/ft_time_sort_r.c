/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_time_sort_r.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/22 13:25:14 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/30 10:24:13 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file_info	*ft_swap_start_list(t_file_info **list_start)
{
	t_file_info	*current;

	current = (*list_start)->next;
	if (current->lstats.st_mtimespec.tv_sec <\
	(*list_start)->lstats.st_mtimespec.tv_sec)
	{
		(*list_start)->next = current->next;
		current->next = *list_start;
		*list_start = current;
	}
	return (*list_start);
}

static int			ft_checktime(t_file_info *one, t_file_info *two)
{
	if (one->lstats.st_mtimespec.tv_sec <\
			two->lstats.st_mtimespec.tv_sec)
	{
		return (1);
	}
	else if (one->lstats.st_mtimespec.tv_sec ==\
			two->lstats.st_mtimespec.tv_sec)
	{
		if (one->lstats.st_mtimespec.tv_nsec <\
			two->lstats.st_mtimespec.tv_nsec)
		{
			return (1);
		}
	}
	return (0);
}

void				ft_time_sort_r(t_file_info **list_start)
{
	t_file_info	*current;
	t_file_info	*previous;
	t_file_info	*future;

	current = (*list_start)->next;
	previous = ft_swap_start_list(list_start);
	future = current->next;
	while (current->next != NULL)
	{
		if (ft_checktime(future, current) == 1)
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
