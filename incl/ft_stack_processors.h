/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stack_processors.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 16:27:27 by aholster       #+#    #+#                */
/*   Updated: 2019/10/16 16:31:02 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_PROCESSORS_H
# define FT_STACK_PROCESSORS_H

# include "./../ft_ls.h"

void		ft_process_ndir_stack(t_fstack *const restrict afstack,\
				const t_flags *const restrict aflags);

void		ft_process_dir_stack(t_fstack *const restrict afstack,\
				const t_flags *const restrict aflags);

#endif
