/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlonger.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 17:00:58 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/23 17:02:35 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t	ft_strlonger(char *str, size_t other_len)
{
	size_t len;

	len = ft_strlen(str);
	return (len > other_len ? len : other_len);
}
