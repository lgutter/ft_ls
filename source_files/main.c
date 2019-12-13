/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 11:48:36 by ivan-tey       #+#    #+#                */
/*   Updated: 2019/12/13 12:02:13 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int			main(int argc, char **argv)
{
	int			i;
	t_options	options;
	int			ret;

	options = 0;
	i = 1;
	ret = ft_find_options(argc, argv, &options);
	if (ret == -1)
		return (-1);
	else
		i = ret;
	while (i < argc)
	{
		ft_print_error("notfound", argv[i]);
		i++;
	}
	return (0);
}
