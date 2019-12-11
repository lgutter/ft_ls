/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 11:48:36 by ivan-tey       #+#    #+#                */
/*   Updated: 2019/12/11 12:05:55 by ivan-tey      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int			main(int argc, char **argv)
{
	int	i;

	i = 0;
	ft_printf("argc = %d\n", argc);
	while (argv && i < argc)
	{
		ft_printf("argv[%d] = %s\n", i, argv[i]);
		i++;
	}
	return (0);
}
