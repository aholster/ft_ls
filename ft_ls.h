/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/12 19:44:46 by aholster       #+#    #+#                */
/*   Updated: 2019/10/13 13:20:32 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "./incl/ft_flag.h"

//# include <stdlib.h>
# include <stdio.h>

# include "./ft_printf/ft_printf.h"//subheader?
//# include <unistd.h>//subheader?

# include <dirent.h> //move to subheader
//# include <sys/stat.h>//subheader?

// # include <sys/types.h>
// # include <pwd.h> //subheader
// # include <uuid/uuid.h>//subheader

// # include <grp.h>//subheader

// # include <sys/xattr.h>//subheader?

// # include <time.h>//subheader

# define USAGE "usage: ft_ls [-Radlrt] [file ...]\n"

/*
**# define USAGE "usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]"
*/

typedef struct	s_fstack
{
	t_finfo *restrict	ndir_stack;
	t_finfo *restrict	dir_stack;
	t_list				*err_list;
}				t_fstack;

# include "./libft/libft.h"

#include "./incl/ft_finfo.h"
void	ft_fstack_del(t_fstack *const restrict afstack);

void	ft_sort_params(char **restrict argv,\
			t_fstack *const restrict afstack,\
			const t_flags *const restrict aflags);

void	ft_run_stacks(t_fstack *const restrict afil_stack,\
			const t_flags *const restrict aflags);

#endif
