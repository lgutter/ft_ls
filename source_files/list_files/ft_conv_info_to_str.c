/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_conv_info_to_str.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lgutter <lgutter@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 17:05:02 by lgutter        #+#    #+#                */
/*   Updated: 2019/12/30 14:57:16 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	ft_filetype_check(mode_t mode)
{
	static const char	filetype[__UINT16_MAX__] = {
		[S_IFSOCK] = 's',
		[S_IFLNK] = 'l',
		[S_IFREG] = '-',
		[S_IFBLK] = 'b',
		[S_IFDIR] = 'd',
		[S_IFCHR] = 'c',
		[S_IFIFO] = 'p',
	};

	return (filetype[mode & S_IFMT]);
}

static void	ft_conv_mode_str(t_file_info *l_item)
{
	const mode_t		mode = l_item->lstats.st_mode;

	l_item->mode[0] = ft_filetype_check(mode);
	l_item->mode[1] = (mode & S_IRUSR) ? 'r' : '-';
	l_item->mode[2] = (mode & S_IWUSR) ? 'w' : '-';
	l_item->mode[3] = (mode & S_IXUSR) ? 'x' : '-';
	if ((mode & S_ISUID))
		l_item->mode[3] = l_item->mode[3] == 'x' ? 's' : 'S';
	l_item->mode[4] = (mode & S_IRGRP) ? 'r' : '-';
	l_item->mode[5] = (mode & S_IWGRP) ? 'w' : '-';
	l_item->mode[6] = (mode & S_IXGRP) ? 'x' : '-';
	if ((mode & S_ISGID))
		l_item->mode[6] = l_item->mode[6] == 'x' ? 's' : 'S';
	l_item->mode[7] = (mode & S_IROTH) ? 'r' : '-';
	l_item->mode[8] = (mode & S_IWOTH) ? 'w' : '-';
	l_item->mode[9] = (mode & S_IXOTH) ? 'x' : '-';
	if ((mode & S_ISVTX))
		l_item->mode[9] = l_item->mode[9] == 'x' ? 't' : 'T';
}

static void	ft_conv_time_str(t_file_info *l_item)
{
	char	*timestr;

	timestr = ctime(&(l_item->lstats.st_mtimespec.tv_sec));
	if (timestr == NULL)
		ft_print_error(errno, l_item->path);
	else
	{
		ft_strncpy(l_item->month, &(timestr[4]), 3);
		ft_strncpy(l_item->date, &(timestr[8]), 2);
		if (l_item->lstats.st_mtimespec.tv_sec < (time(NULL) - 15724800) ||\
			l_item->lstats.st_mtimespec.tv_sec > time(NULL))
			ft_strncpy(l_item->tiye, &(timestr[20]), 4);
		else
			ft_strncpy(l_item->tiye, &(timestr[11]), 5);
	}
}

void		ft_conv_info_to_str(t_file_info *l_item)
{
	char *str;

	while (l_item != NULL)
	{
		ft_conv_mode_str(l_item);
		str = ft_itoa(l_item->lstats.st_nlink);
		ft_strncpy(l_item->links, str, 8);
		free(str);
		str = ft_ulltoa_base_low(l_item->lstats.st_size, 10);
		ft_strncpy(l_item->size, str, 32);
		free(str);
		ft_conv_time_str(l_item);
		l_item = l_item->next;
	}
}
