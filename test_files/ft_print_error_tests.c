/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_error_tests.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 12:24:00 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/20 13:18:00 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "ft_ls.h"


static void redirect_std_err(void)
{
    cr_redirect_stderr();
}

Test(ft_print_error_tests, print_usage, .init = redirect_std_err)
{
	ft_print_error(EUSAGE, NULL);
	fflush(stderr);

	cr_assert_stderr_eq_str("usage: ft_ls [-Ralrt] [file ...]\n");
}

Test(ft_print_error_tests, print_no_such, .init = redirect_std_err)
{
	ft_print_error(ENOENT, "iets.c");
	fflush(stderr);

	cr_assert_stderr_eq_str("ft_ls: iets.c: No such file or directory\n");
}

Test(ft_print_error_tests, print_access_denied, .init = redirect_std_err)
{
	ft_print_error(EACCES, "iets");
	fflush(stderr);

	cr_assert_stderr_eq_str("ft_ls: iets: Permission denied\n");
}

Test(ft_print_error_tests, print_unkown, .init = redirect_std_err)
{
	ft_print_error(424242, "iets");
	fflush(stderr);

	cr_assert_stderr_eq_str("ft_ls: 424242: Unknown errno\n");
}
