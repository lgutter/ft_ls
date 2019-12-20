/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dir_to_list_tests.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/18 10:47:50 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/20 17:00:04 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "ft_ls.h"

static void redirect_std_err(void)
{
    cr_redirect_stderr();
}

static void redirect_std_out(void)
{
    cr_redirect_stdout();
}

Test(ft_dir_to_list_tests, dir_does_exist, .init = redirect_std_out)
{
	int ret;

	ret = ft_dir_to_list("source_files", e_opt_a);
	fflush(stdout);
	cr_assert_eq(ret, 0);
}

Test(ft_dir_to_list_tests, dir_doesnt_exist, .init = redirect_std_err)
{
	int ret;

	ret = ft_dir_to_list("doesntexist", e_opt_a);
	fflush(stderr);
	cr_assert_stderr_eq_str("ft_ls: doesntexist: No such file or directory\n");
	cr_assert_eq(ret, -1);
}

Test(ft_dir_to_list_tests, dir_not_a_dir, .init = redirect_std_err)
{
	int ret;

	ret = ft_dir_to_list("ft_ls.h", e_opt_a);
	fflush(stderr);
	cr_assert_eq(ret, -1);
}
