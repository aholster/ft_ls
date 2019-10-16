/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_run_stacks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/12 13:20:09 by aholster       #+#    #+#                */
/*   Updated: 2019/10/16 16:08:44 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "./incl/ft_stack_sorters.h"

static void	list_print(t_finfo *elem)
{
//	printf("node:%p, %s\t", elem, elem->s_name);
	printf("time:%ld, %ld,\t%s\n", elem->inf.st_atimespec.tv_sec,\
									elem->inf.st_atimespec.tv_nsec,\
									elem->s_name);
//	printf("%llu\n", elem->inf.st_ino);
}

void		ft_run_stacks(t_fstack *const restrict afstack,\
				const t_flags *const restrict aflags)
{
	if (afstack->err_queue != NULL)
	{
		ft_process_err_queue(afstack, aflags);
	}
	if (afstack->ndir_stack != NULL)
	{
		ft_process_ndir_stack(afstack, aflags);
	}
	if (afstack->dir_stack != NULL)
	{
		printf("now showing dir list\n");
		finfo_lstiter(afstack->dir_stack, &list_print);
//		ft_process_dir_stack(afstack, aflags);
	}
	ft_fstack_del(afstack);
}
