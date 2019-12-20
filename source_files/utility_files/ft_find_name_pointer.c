/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_find_name_pointer.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/20 12:10:58 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/20 12:47:22 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_find_name_pointer(char path[PATH_MAX + 1])
{
	char *name_pointer;

	name_pointer = &(path[0]);
	while (*name_pointer != '\0' && name_pointer != &(path[PATH_MAX]))
		name_pointer++;
	while (*name_pointer != '/' && name_pointer != &(path[0]))
		name_pointer--;
	return (name_pointer + (name_pointer[0] == '/'));
}
