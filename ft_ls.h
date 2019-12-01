/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ls.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/12 19:44:46 by aholster       #+#    #+#                */
/*   Updated: 2019/12/01 02:26:02 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "./libft/libft.h"
# include "./incl/finfo.h"

# define USAGE "usage: ft_ls [-BCFGLRTUabcdfgilmnopqrtuwx1] [file ...]\n"

/*
** #     	   "usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]"
*/

typedef struct			s_fsort
{
	t_finfo_queue		ndir_queue;
	t_finfo_queue		dir_queue;
	t_queue				err_queue;
}						t_fsort;

typedef struct			s_fstack
{
	t_finfo				*ndir_stack;
	t_finfo				*dir_stack;
	t_list				*err_queue;
}						t_fstack;

void					ft_error_cleanup(t_fstack *const restrict afstack);

void					ft_fstack_del(t_fstack *const restrict afstack);

void					ft_sort_params(char **restrict argv,\
							t_fstack *const restrict afstack,\
							const t_flags aflags);

void					ft_run_stacks(t_fstack *const restrict afstack,\
							const t_flags aflags);

void					ft_relevant_time(\
							const struct timespec **const arec_time,\
							const struct stat *const restrict astat,\
							const t_flags aflags);

#endif
