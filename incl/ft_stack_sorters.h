/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stack_sorters.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/13 13:59:38 by aholster       #+#    #+#                */
/*   Updated: 2019/12/03 06:44:37 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_SORTERS_H
# define FT_STACK_SORTERS_H

# include "../ft_ls.h"

void		ft_sortnprocess_err_queue(t_fstack *const restrict afstack,\
				const t_flags aflags);

void		ft_sort_finfo_stack(t_finfo_queue *const restrict afinfo_stack,\
				const t_flags aflags);

t_decider	ft_sorter_method(const t_flags aflags);
t_decider	ft_sorter_method_rev(const t_flags aflags);

#endif
