/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_error_tests.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 12:24:00 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/13 14:11:11 by ivan-tey      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "ft_ls.h"


static void redirect_std_err(void)
{
    cr_redirect_stderr();
}

Test(stupid, ft_ls_error_test_1, .init = redirect_std_err)
{
	ft_print_error("usage", NULL);
	fflush(stderr);

	cr_assert_stderr_eq_str("usage: ft_ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
}

Test(stupid, ft_ls_error_test_2, .init = redirect_std_err)
{
	ft_print_error("notfound", "iets.c");
	fflush(stderr);

	cr_assert_stderr_eq_str("ft_ls: iets.c: No such file or directory\n");
}

Test(stupid, ft_ls_error_test_3, .init = redirect_std_err)
{
	ft_print_error("permission", "iets");
	fflush(stderr);

	cr_assert_stderr_eq_str("ft_ls: iets: Permission denied\n");
}
