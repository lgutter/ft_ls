/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_find_options_tests.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 12:20:50 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/13 12:27:46 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include "ft_ls.h"

Test(ft_find_options_tests, all_options_in_single_arg)
{
	int argc = 2;
	char **argv = (char **)malloc(sizeof(char *) * argc);
	t_options options;
	t_options expected;

	argv[0] = "test";
	argv[1] = "-artlR";
	ft_find_options(argc, argv, &options);

	expected = (e_oa | e_or | e_ot | e_ol | e_oR);
	cr_assert_eq(options, expected);
}
