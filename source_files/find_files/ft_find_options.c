/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_find_options.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 18:04:22 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/13 11:53:53 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_check_options(int i, char *str, t_options *options)
{
	if (str[i] == '-' && str[i + 1] == '\0')
		return (2);
	while (str[i] != '\0')
	{
		if (str[i] == 'l')
			*options |= e_ol;
		else if (str[i] == 'R')
			*options |= e_oR;
		else if (str[i] == 'a')
			*options |= e_oa;
		else if (str[i] == 'r')
			*options |= e_or;
		else if (str[i] == 't')
			*options |= e_ot;
		else
		{
			ft_print_error("option", &(str[i]));
			ft_print_error("usage", NULL);
			return (-1);
		}
		i++;
	}
	return (0);
}

int			ft_find_options(int argc, char **argv, t_options *options)
{
	int i;
	int ret;

	i = 1;
	while (i < argc && argv[i][0] == '-')
	{
		ret = ft_check_options(1, argv[i], options);
		if (ret == -1)
			return (-1);
		else if (ret == 2)
		{
			return (i + 1);
		}
		i++;
	}
	return (i);
}
