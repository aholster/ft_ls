/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/12 19:44:46 by aholster       #+#    #+#                */
/*   Updated: 2019/11/11 22:44:16 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
// # include "./ft_printf/ft_printf.h"


# include "./libft/libft.h"
# include "./incl/finfo.h"

# define USAGE "usage: ft_ls [-LRTUacdfilrtu1] [file ...]\n"

/*
** # define USAGE "usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]"
*/

typedef struct			s_fstack
{
	t_finfo *restrict	ndir_stack;
	t_finfo *restrict	dir_stack;
	t_list				*err_queue;
}						t_fstack;

void					ft_error_cleanup(t_fstack *const restrict afstack);

void					ft_fstack_del(t_fstack *const restrict afstack);

void					ft_sort_params(char **restrict argv,\
							t_fstack *const restrict afstack,\
							const t_flags *const restrict aflags);

void					ft_run_stacks(t_fstack *const restrict afstack,\
							const t_flags *const restrict aflags);

#endif
