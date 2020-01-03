/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort_list.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/22 11:49:18 by lgutter        #+#    #+#                */
/*   Updated: 2020/01/03 12:37:51 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_check_lex_sort(t_file_info *current, t_options options)
{
	if ((options & e_opt_r) != 0)
	{
		while (current->next != NULL)
		{
			if (ft_strcmp(current->path, (current->next)->path) < 0)
				return (-1);
			current = current->next;
		}
	}
	else
	{
		while (current->next != NULL)
		{
			if (ft_strcmp(current->path, (current->next)->path) > 0)
				return (-1);
			current = current->next;
		}
	}
	return (0);
}

static int	ft_check_time_rev(t_file_info *current)
{
	while (current->next != NULL)
	{
		if ((current->next)->lstats.st_mtimespec.tv_sec <\
			current->lstats.st_mtimespec.tv_sec)
			return (-1);
		else if ((current->next)->lstats.st_mtimespec.tv_sec ==\
			current->lstats.st_mtimespec.tv_sec)
		{
			if ((current->next)->lstats.st_mtimespec.tv_nsec <\
				current->lstats.st_mtimespec.tv_nsec)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

static int	ft_check_time_sort(t_file_info *current, t_options options)
{
	if ((options & e_opt_r) != 0)
	{
		return (ft_check_time_rev(current));
	}
	else
	{
		while (current->next != NULL)
		{
			if ((current->next)->lstats.st_mtimespec.tv_sec >\
				current->lstats.st_mtimespec.tv_sec)
			{
				return (-1);
			}
			else if ((current->next)->lstats.st_mtimespec.tv_sec ==\
				current->lstats.st_mtimespec.tv_sec)
			{
				if ((current->next)->lstats.st_mtimespec.tv_nsec >\
					current->lstats.st_mtimespec.tv_nsec)
					return (-1);
			}
			current = current->next;
		}
	}
	return (0);
}

void		ft_sort_list(t_file_info **list_start, t_options options)
{
	if ((options & e_opt_r) == 0)
	{
		while (ft_check_lex_sort(*list_start, options) == -1)
			ft_lex_sort(list_start);
		if ((options & e_opt_t) != 0)
		{
			while (ft_check_time_sort(*list_start, options) == -1)
				ft_time_sort(list_start);
		}
	}
	else
	{
		while (ft_check_lex_sort(*list_start, options) == -1)
			ft_lex_sort_r(list_start);
		if ((options & e_opt_t) != 0)
		{
			while (ft_check_time_sort(*list_start, options) == -1)
				ft_time_sort_r(list_start);
		}
	}
}
