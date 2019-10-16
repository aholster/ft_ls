/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_run_stacks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/12 13:20:09 by aholster       #+#    #+#                */
/*   Updated: 2019/10/16 17:53:12 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "./incl/ft_stack_sorters.h"
#include "./incl/ft_stack_processors.h"

void		ft_run_stacks(t_fstack *const restrict afstack,\
				const t_flags *const restrict aflags)
{
	if (afstack->err_queue != NULL)
	{
		ft_sortnprocess_err_queue(afstack, aflags);
	}
	if (afstack->ndir_stack != NULL)
	{
		if (((*aflags) & flg_f) == 0)
		{
			ft_sort_finfo_stack(&(afstack->ndir_stack), aflags);
		}
		ft_process_ndir_stack(afstack, aflags);
	}
	if (afstack->dir_stack != NULL)
	{
		if (((*aflags) & flg_f) == 0)
		{
			ft_sort_finfo_stack(&(afstack->dir_stack), aflags);
		}
		ft_process_dir_stack(afstack, aflags);
	}
	ft_fstack_del(afstack);
}
