/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_ndir_stack.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 10:40:04 by aholster       #+#    #+#                */
/*   Updated: 2019/11/26 10:12:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_stack_processors.h"

void		ft_process_ndir_stack(t_fstack *const restrict afstack,\
				const t_flags aflags)
{
	t_list				*out_stack;
	t_print_widths		widths;

	out_stack = NULL;
	ft_bzero(&widths, sizeof(t_print_widths));
	if (ft_process_files_to_txt(&(afstack->ndir_stack),\
		&out_stack, &widths, aflags) == -1)
	{
		ft_lstdel(&out_stack, &ft_del);
		ft_error_cleanup(afstack);
	}
	if (ft_printer(out_stack, &widths, aflags) == -1)
	{
		ft_lstdel(&out_stack, &ft_del);
		ft_error_cleanup(afstack);
	}
	ft_lstdel(&out_stack, &ft_del);
}
