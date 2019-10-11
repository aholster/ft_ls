/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/12 19:44:46 by aholster       #+#    #+#                */
/*   Updated: 2019/10/11 13:35:17 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "./incl/ft_flag.h"

# include <stdlib.h>
# include <stdio.h> //currently used for erroring

# include "./ft_printf/ft_printf.h"//subheader?
# include <unistd.h>//subheader?

# include <dirent.h> //move to subheader
//# include <sys/stat.h>//subheader?

// # include <sys/types.h>
// # include <pwd.h> //subheader
// # include <uuid/uuid.h>//subheader

// # include <grp.h>//subheader

// # include <sys/xattr.h>//subheader?

// # include <time.h>//subheader

# define USAGE "usage: ft_ls [-Ralrt] [file ...]"

/*
**# define USAGE "usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]"
*/

#include "./libft/libft.h"

void	ft_sort_params(t_argstruct *const restrict args,\
			t_list **const restrict andir_list,\
			t_list **const restrict adir_list,\
			t_flags *const restrict aflags);

#endif
