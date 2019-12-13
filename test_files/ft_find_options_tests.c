/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_find_options_tests.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 12:20:50 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/13 14:13:25 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "ft_ls.h"


Test(ft_find_options_tests, all_options_in_single_arg)
{
	int argc = 2;
	int ret;
	char **argv = (char **)malloc(sizeof(char *) * argc);
	t_options options = 0;
	t_options expected = 0;

	argv[0] = "test";
	argv[1] = "-artlR";
	ret = ft_find_options(argc, argv, &options);

	expected = (e_oa | e_or | e_ot | e_ol | e_oR);
	cr_assert_eq(ret, 2);
	cr_assert_eq(options, expected);
}

Test(ft_find_options_tests, double_dash_option_first)
{
	int argc = 2;
	int ret;
	char **argv = (char **)malloc(sizeof(char *) * argc);
	t_options options = 0;
	t_options expected = 0;

	argv[0] = "test";
	argv[1] = "--";
	ret = ft_find_options(argc, argv, &options);
	cr_assert_eq(ret, 2);
	cr_assert_eq(options, expected);
}

Test(ft_find_options_tests, all_options_in_two_args)
{
	int argc = 3;
	int ret;
	char **argv = (char **)malloc(sizeof(char *) * argc);
	t_options options = 0;
	t_options expected = 0;

	argv[0] = "test";
	argv[1] = "-ar";
	argv[2] = "-tlR";
	ret = ft_find_options(argc, argv, &options);

	expected = (e_oa | e_or | e_ot | e_ol | e_oR);
	cr_assert_eq(ret, 3);
	cr_assert_eq(options, expected);
}

Test(ft_find_options_tests, all_options_in_two_args_duplicates)
{
	int argc = 3;
	int ret;
	char **argv = (char **)malloc(sizeof(char *) * argc);
	t_options options = 0;
	t_options expected = 0;

	argv[0] = "test";
	argv[1] = "-aRr";
	argv[2] = "-talR";
	ret = ft_find_options(argc, argv, &options);

	expected = (e_oa | e_or | e_ot | e_ol | e_oR);
	cr_assert_eq(ret, 3);
	cr_assert_eq(options, expected);
}

Test(ft_find_options_tests, only_duplicates)
{
	int argc = 3;
	int ret;
	char **argv = (char **)malloc(sizeof(char *) * argc);
	t_options options = 0;
	t_options expected = 0;

	argv[0] = "test";
	argv[1] = "-aRt";
	argv[2] = "-taR";
	ret = ft_find_options(argc, argv, &options);

	expected = (e_oa | e_ot | e_oR);
	cr_assert_eq(ret, 3);
	cr_assert_eq(options, expected);
}

Test(ft_find_options_tests, only_invalid_option)
{
	int argc = 2;
	int ret;
	char **argv = (char **)malloc(sizeof(char *) * argc);
	t_options options = 0;
	t_options expected = 0;

	argv[0] = "test";
	argv[1] = "-j";
	close(2);
	ret = ft_find_options(argc, argv, &options);
	cr_assert_eq(ret, -1);
	cr_assert_eq(options, expected);
}

Test(ft_find_options_tests, two_args_invalid_option_first)
{
	int argc = 3;
	int ret;
	char **argv = (char **)malloc(sizeof(char *) * argc);
	t_options options = 0;
	t_options expected = 0;

	argv[0] = "test";
	argv[1] = "-ajRt";
	argv[2] = "-taR";
	close(2);
	ret = ft_find_options(argc, argv, &options);
	expected = (e_oa);
	cr_assert_eq(ret, -1);
	cr_assert_eq(options, expected);
}

Test(ft_find_options_tests, two_args_invalid_option_last)
{
	int argc = 3;
	int ret;
	char **argv = (char **)malloc(sizeof(char *) * argc);
	t_options options = 0;
	t_options expected = 0;

	argv[0] = "test";
	argv[1] = "-aRt";
	argv[2] = "-taRj";
	close(2);
	ret = ft_find_options(argc, argv, &options);
	expected = (e_oa | e_ot | e_oR);
	cr_assert_eq(ret, -1);
	cr_assert_eq(options, expected);
}

