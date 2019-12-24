/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 11:33:09 by ivan-tey       #+#    #+#                */
/*   Updated: 2019/12/24 13:53:30 by lgutter       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <limits.h>
# include <errno.h>
# include <string.h>

# include "ft_printf.h"

/*
**	enumerations for the options
*/
enum					e_options
{
	e_opt_l = 1 << 0,
	e_opt_R = 1 << 1,
	e_opt_a = 1 << 2,
	e_opt_r = 1 << 3,
	e_opt_t = 1 << 4,
};

/*
**	typedef of an unsigned long for the options,
**	this is where the above listen enums are stored.
*/
typedef unsigned long	t_options;

/*
**	struct with info of the file:
**		stats: struct as returned by the function lstat
**		path: complete path of the file as given as argument
**		name_pointer: pointer to the position in path where the filename starts
**		mode: st_mode converted to string
**		links: st_nlink converted to string
**		size: st_size converted to string
**		month: the month extracted from st_mtimespec converted to string
**		date: the date(day) extracted from st_mtimespec converted to string
**		tiye: the time/year extracted from st_mtimespec converted to string
**		u_name: name of the user as given by getpwuid
**		g_name: name of the group as given by getgrgid
**		link_path: the path contained in the symlink as given by readlink
**		next: a pointer to the next element in the list of info structs
*/
typedef struct			s_file_info
{
	struct stat			stats;
	struct stat			lstats;
	char				path[PATH_MAX + 1];
	char				*name_pointer;
	char				mode[10 + 1];
	char				links[8 + 1];
	char				size[32 + 1];
	char				month[3 + 1];
	char				date[2 + 1];
	char				tiye[5 + 1];
	char				u_name[NAME_MAX + 1];
	char				g_name[NAME_MAX + 1];
	char				link_path[PATH_MAX + 1];
	struct s_file_info	*next;
}						t_file_info;

/*
**	Struct that holds the minimum field width of every field in the long output.
**	To clarify, a list of every field:
**		mode: the permissions of the file
**		links: the amount of links to the file
**		user: the owner of the file
**		group: the group of the file
**		size: the size of the file in bytes
**		month: the month in which the file was last modified
**		date: the date on which the file was last modified
**		tiye: the time or year when the file was last modified
*/
typedef struct			s_field_width
{
	size_t				links;
	size_t				user;
	size_t				group;
	size_t				size;
	size_t				date;
	size_t				blocks;
}						t_width;

/*
**	Core functions
*/

int						main(int argc, char **argv);
int						ft_ls(int filecount,\
								char **filenames, t_options options);

/*
** Find functions
*/

int						ft_find_options(int argc,\
										char **argv, t_options *options);

/*
** List functions
*/

t_file_info				*ft_stats_to_list(char *filename,\
										t_file_info **list_start);
int						ft_dir_to_list(char *dirname, t_options options);
void					ft_sort_list(t_file_info **list_start,\
										t_options options);
void					ft_lex_sort(t_file_info **list_start);
void					ft_lex_sort_r(t_file_info **list_start);
void					ft_time_sort(t_file_info **list_start);
void					ft_time_sort_r(t_file_info **list_start);
void					ft_conv_info_to_str(t_file_info *l_item);

/*
**	Utility functions
*/

char					*ft_find_name_pointer(char path[PATH_MAX + 1]);
void					ft_print_files_info(t_file_info *list_start,\
											t_options options);
void					ft_print_error(int errnumber, char *errstr);
void					ft_print_opt_error(char option);
void					ft_print_usage(void);
void					*ft_error_free(void **memory);
size_t					ft_strlonger(size_t other_len, char *str);

#endif
