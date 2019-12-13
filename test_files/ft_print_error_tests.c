/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_error_tests.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 12:24:00 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/13 13:42:26 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "ft_ls.h"


static void redirect_std_err(void)
{
    cr_redirect_stderr();
}

Test(stupid, very_stupid_test_1, .init = redirect_std_err)
{
	ft_print_error("usage", NULL);
	fflush(stderr);

	cr_assert_stderr_eq_str("usage: ft_ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
}
