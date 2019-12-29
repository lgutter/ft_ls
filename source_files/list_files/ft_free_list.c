/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_list.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/29 14:52:36 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/29 15:22:03 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_free_list(t_file_info **list_start)
{
	t_file_info *current;
	t_file_info *temp;

	current = *list_start;
	*list_start = NULL;
	while (current->next != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
		temp = NULL;
	}
	free(current);
	current = NULL;
}
