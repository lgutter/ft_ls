/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stupidtest.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 13:25:59 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/11 13:29:55 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "ft_printf.h"

static void redirect_std_out(void)
{
    cr_redirect_stdout();
}

Test(stupid, very_stupid_test_1, .init = redirect_std_out)
{
	ft_printf("hoi");
	fflush(stdout);

	cr_assert_stdout_eq_str("hoi");
}
