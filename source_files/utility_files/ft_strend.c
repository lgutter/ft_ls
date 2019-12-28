/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strend.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/28 16:33:46 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/28 17:23:06 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_strend(const char *source, const char *end)
{
	size_t index;
	size_t judex;

	index = ft_strlen(source);
	judex = ft_strlen(end);
	while (source[index] == end[judex])
	{
		if (judex == 0)
		{
			return (1);
		}
		index--;
		judex--;
	}
	return (0);
}
