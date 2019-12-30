/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stats_to_list_tests.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/18 10:47:50 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/30 17:13:45 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "ft_ls.h"

static void redirect_std_err(void)
{
    cr_redirect_stderr();
}

Test(ft_stats_to_list_tests, simple_existent_file_empty_list)
{
	int argc = 2;
	t_file_info *ret;
	t_file_info *list_start = NULL;
	t_options options = 0;
	char **filenames = (char **)malloc(sizeof(char *) * argc);

	filenames[0] = "test";
	filenames[1] = "ft_ls.h";
	ret = ft_stats_to_list(filenames[1],  &list_start, options);

	cr_assert_neq(ret, NULL);
	cr_assert_str_eq(ret->path, filenames[1]);
}
Test(ft_stats_to_list_tests, simple_nonexistent_file_empty_list, .init = redirect_std_err)
{
	int argc = 2;
	t_file_info *ret;
	t_file_info *list_start = NULL;
	t_options options = 0;
	char **filenames = (char **)malloc(sizeof(char *) * argc);

	filenames[0] = "test";
	filenames[1] = "this/file/does/not/exist";
	ret = ft_stats_to_list(filenames[1],  &list_start, options);
	fflush(stderr);

	cr_assert_stderr_eq_str("ft_ls: this/file/does/not/exist: No such file or directory\n");
	cr_assert_eq(ret, NULL);
}

Test(ft_stats_to_list_tests, simple_existent_files_empty_list)
{
	int argc = 3;
	size_t i = 0;
	t_file_info *ret;
	t_file_info *list_start = NULL;
	t_options options = 0;
	char **filenames = (char **)malloc(sizeof(char *) * argc);

	filenames[0] = "test";
	filenames[1] = "ft_ls.h";
	filenames[2] = "ft_printf";
	ret = ft_stats_to_list(filenames[1],  &list_start, options);
	cr_assert_neq(ret, NULL);
	ret = ft_stats_to_list(filenames[2],  &list_start, options);
	cr_assert_neq(ret, NULL);

	cr_assert_neq(list_start, NULL);
	while (list_start != NULL)
	{
		cr_assert_str_eq(list_start->path, filenames[i + 1]);
		list_start = list_start->next;
		i++;
	}
	cr_assert_eq(i, 2);
}

Test(ft_stats_to_list_tests, simple_existent_3_files_empty_list)
{
	int argc = 4;
	size_t i = 0;
	t_file_info *ret;
	t_file_info *list_start = NULL;
	t_options options = 0;
	char **filenames = (char **)malloc(sizeof(char *) * argc);

	filenames[0] = "test";
	filenames[1] = "ft_ls.h";
	filenames[2] = "ft_printf";
	filenames[3] = "end2endls.sh";
	ret = ft_stats_to_list(filenames[1],  &list_start, options);
	cr_assert_neq(ret, NULL);
	ret = ft_stats_to_list(filenames[2],  &list_start, options);
	cr_assert_neq(ret, NULL);
	ret = ft_stats_to_list(filenames[3],  &list_start, options);
	cr_assert_neq(ret, NULL);

	cr_assert_neq(list_start, NULL);
	while (list_start != NULL)
	{
		cr_assert_str_eq(list_start->path, filenames[i + 1]);
		list_start = list_start->next;
		i++;
	}
	cr_assert_eq(i, 3);
}

Test(ft_stats_to_list_tests, link_file_empty_list)
{
	int argc = 2;
	size_t i = 0;
	t_file_info *ret;
	t_file_info *list_start = NULL;
	t_options options = 0;
	char **filenames = (char **)malloc(sizeof(char *) * argc);

	filenames[0] = "test";
	filenames[1] = "test_files/files_for_tests/link_to_ft_ls_h";
	ret = ft_stats_to_list(filenames[1],  &list_start, options);
	cr_assert_neq(ret, NULL);

	cr_assert_neq(list_start, NULL);
	while (list_start != NULL)
	{
		cr_assert_str_eq(list_start->path, filenames[i + 1]);
		list_start = list_start->next;
		i++;
	}
	cr_assert_eq(i, 1);
}

