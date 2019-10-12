/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/12 19:44:46 by aholster       #+#    #+#                */
/*   Updated: 2019/10/12 19:08:32 by aholster      ########   odam.nl         */
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

# define USAGE "usage: ft_ls [-Ralrt] [file ...]\n"

/*
**# define USAGE "usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]"
*/

# include "./libft/libft.h"

#include "./incl/ft_finfo.h"
void	ft_sort_params(char **restrict argv,\
			t_finfo *restrict *const restrict andir_stack,\
			t_finfo *restrict *const restrict adir_stack,\
			const t_flags *const restrict aflags);

void	ft_run_stacks(t_finfo *restrict *const restrict andir_stack,\
			t_finfo *restrict *const restrict adir_stack,\
			const t_flags *const restrict aflags);

#endif
