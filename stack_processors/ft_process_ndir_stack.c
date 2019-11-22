/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_ndir_stack.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 10:40:04 by aholster       #+#    #+#                */
/*   Updated: 2019/11/22 08:33:22 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_stack_processors.h"

void		ft_process_ndir_stack(t_fstack *const restrict afstack,\
				const t_flags aflags)
{
	t_list					*out_stack;
	int						max_len;

	out_stack = NULL;
	max_len = 0;
	if (ft_process_files_to_txt(&(afstack->ndir_stack),\
		&out_stack, &max_len, aflags) == -1)
	{
		ft_lstdel(&out_stack, &ft_del);
		ft_error_cleanup(afstack);
	}
	if (ft_printer(out_stack, max_len, aflags) == -1)
	{
		ft_lstdel(&out_stack, &ft_del);
		ft_error_cleanup(afstack);
	}
	ft_lstdel(&out_stack, &ft_del);
}
