/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error_free.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 14:18:23 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/17 14:26:24 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	*ft_error_free(void **memory)
{
	free(*memory);
	*memory = NULL;
	return (NULL);
}
