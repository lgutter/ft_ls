/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 11:48:36 by ivan-tey       #+#    #+#                */
/*   Updated: 2019/12/30 10:49:03 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int argc, char **argv)
{
	int					i;
	t_options			options;
	int					ret;
	static char			*noarg = ".";

	options = 0;
	i = 1;
	ret = ft_find_options(argc, argv, &options);
	if (ret == -1)
		return (1);
	else
		i = ret;
	if ((argc - i) == 0)
		ret = ft_ls(1, &noarg, options);
	else
		ret = ft_ls(argc - i, &(argv[i]), options);
	return (ret);
}
