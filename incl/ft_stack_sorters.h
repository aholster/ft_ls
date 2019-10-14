/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stack_sorters.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/13 13:59:38 by aholster       #+#    #+#                */
/*   Updated: 2019/10/14 15:11:16 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_STACK_SORTERS_H
# define FT_STACK_SORTERS_H

# include "./../ft_ls.h"

void		ft_process_err_queue(t_fstack *const restrict afstack,\
				const t_flags *const restrict aflags);

void		ft_process_ndir_stack(t_fstack *const restrict afstack,\
				const t_flags *const restrict aflags);

void		ft_process_dir_stack(t_fstack *const restrict afstack,\
				const t_flags *const restrict aflags);

void		ft_sort_finfo_stack(\
				t_finfo *restrict *const restrict afinfo_stack,\
				const t_flags *const restrict aflags);

t_decider	ft_sorter_method(const t_flags *const restrict aflags);
t_decider	ft_sorter_method_rev(const t_flags *const restrict aflags);


#endif
