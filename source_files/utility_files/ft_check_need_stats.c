/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_check_need_stats.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 12:19:51 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/30 12:23:15 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_check_need_stats(t_options options, char firstchar, char type)
{
	if ((options & e_args) == 0)
	{
		return (1);
	}
	if (((options & e_opt_l) != 0 || (options & e_opt_t) != 0 || type == 'a'))
	{
		if ((options & e_opt_a) != 0)
		{
			return (1);
		}
		else if (firstchar != '.')
		{
			return (1);
		}
		else
		{
			return (0);
		}
	}
	else
	{
		return (0);
	}
}
