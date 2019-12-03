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

#include <stdio.h>

#include "ft_ls.h"
#include "./incl/ft_stack_sorters.h"
#include "./incl/ft_stack_processors.h"

void		ft_fstack_del(t_fstack *const restrict afqueues)
{
	finfo_del(&(afqueues->ndir_queue));
	finfo_del(&(afqueues->dir_queue));
	ft_lstdel(&(afqueues->err_queue.head), &ft_del);
	ft_bzero(afqueues, sizeof(t_fstack));
}

void		ft_error_cleanup(t_fstack *const restrict afqueues)
{
	perror("ft_ls");
	ft_fstack_del(afqueues);
	exit(-1);
}

static int	is_only_one_dir(const t_fstack *const restrict afqueues)
{
	if (afqueues->err_queue.head == NULL && afqueues->ndir_queue.head == NULL &&
	(afqueues->dir_queue.head == NULL || afqueues->dir_queue.head->next == NULL))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

void		ft_run_stacks(t_fstack *const restrict afqueues,\
				const t_flags aflags)
{
	const int	is_sdir = is_only_one_dir(afqueues);

	if (afqueues->err_queue.head != NULL)
	{
		ft_sortnprocess_err_queue(afqueues, aflags);
	}
	if (afqueues->ndir_queue.head != NULL)
	{
		if ((aflags & flg_f) == 0)
		{
			ft_sort_finfo_stack(&(afqueues->ndir_queue), aflags);
		}
		if (ft_process_ndir_stack(&(afqueues->ndir_queue.head), aflags) == -1)
		{
			ft_error_cleanup(afqueues);
		}
	}
	if (afqueues->dir_queue.head != NULL)
	{
		if ((aflags & flg_f) == 0)
		{
			ft_sort_finfo_stack(&(afqueues->dir_queue), aflags);
		}
		if (ft_process_dir_stack(&(afqueues->dir_queue), is_sdir, aflags) == -1)
		{
			ft_error_cleanup(afqueues);
		}
	}
	ft_fstack_del(afqueues);
}
