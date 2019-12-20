/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivan-tey <ivan-tey@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 11:33:09 by ivan-tey       #+#    #+#                */
/*   Updated: 2019/12/20 21:38:40 by lgutter       ########   odam.nl         */
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
**	struct with info of a file:
**		stats: struct as returned by the function lstat
**		path: complete path of the file as given as argument
**		name_pointer: pointer to the position in path where the filename starts
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
	char				u_name[NAME_MAX + 1];
	char				g_name[NAME_MAX + 1];
	char				link_path[PATH_MAX + 1];
	struct s_file_info	*next;
}						t_file_info;

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

/*
**	Utility functions
*/

char					*ft_find_name_pointer(char path[PATH_MAX + 1]);
void					ft_print_error(int errnumber, char *errstr);
void					ft_print_opt_error(char option);
void					ft_print_usage(void);
void					*ft_error_free(void **memory);

#endif
