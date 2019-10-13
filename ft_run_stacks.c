/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_run_stacks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/12 13:20:09 by aholster       #+#    #+#                */
/*   Updated: 2019/10/13 18:10:18 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "./incl/ft_stack_sorters.h"

#include <sys/stat.h>

static void	list_print(t_finfo *elem)
{
	printf("node:%p, %s\t", elem, elem->s_name);
	printf("%llu\n", elem->inf.st_ino);
}

void		ft_run_stacks(t_fstack *const restrict afstack,\
				const t_flags *const restrict aflags)
{
	if (afstack->err_stack != NULL)
	{
		ft_sort_err_stack(afstack);
	}
	finfo_lstiter(afstack->ndir_stack, &list_print);
	printf("now showing dir list\n");
	finfo_lstiter(afstack->dir_stack, &list_print);
	ft_fstack_del(afstack);
	(void)aflags;
}
