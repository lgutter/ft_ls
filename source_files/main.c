/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 11:48:36 by ivan-tey       #+#    #+#                */
/*   Updated: 2019/12/11 13:38:07 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

int			main(int argc, char **argv)
{
	int	i;

	i = 1;
	while (argv && i < argc)
	{
		dprintf(2, "ls: %s: No such file or directory\n", argv[i]);
		i++;
	}
	return (0);
}
