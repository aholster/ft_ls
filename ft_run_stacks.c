/* *************************************************************************/
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_run_stacks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/12 13:20:09 by aholster       #+#    #+#                */
/*   Updated: 2019/11/13 16:30:48 by aholster      ########   odam.nl         */
/*                                                                            */
/* *************************************************************************/

#include "ft_ls.h"
#include "./incl/ft_stack_sorters.h"
#include "./incl/ft_stack_processors.h"

static int	is_only_one_dir(const t_fstack *const restrict afstack)
{
	if (afstack->err_queue || afstack->ndir_stack)
	{
		return (0);
	}
	else if (afstack->dir_stack != NULL && afstack->dir_stack->next != NULL)
	{
		return (0);
	}
	else
	{
		return (1);
	}
}

void		ft_run_stacks(t_fstack *const restrict afstack,\
				const t_flags aflags)
{
	const int	is_sdir = is_only_one_dir(afstack);

	if (afstack->err_queue != NULL)
	{
		ft_sortnprocess_err_queue(afstack, aflags);
	}
	if (afstack->ndir_stack != NULL)
	{
		if ((aflags & flg_f) == 0)
		{
			ft_sort_finfo_stack(&(afstack->ndir_stack), aflags);
		}
		ft_process_ndir_stack(afstack, aflags);
	}
	if (afstack->dir_stack != NULL)
	{
		if ((aflags & flg_f) == 0)
		{
			ft_sort_finfo_stack(&(afstack->dir_stack), aflags);
		}
		ft_process_dir_stack(afstack, is_sdir, aflags);
	}
	ft_fstack_del(afstack);
}
