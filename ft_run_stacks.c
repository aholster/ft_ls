/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_run_stacks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/12 13:20:09 by aholster       #+#    #+#                */
/*   Updated: 2019/10/13 13:20:34 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <sys/stat.h>

static void	list_print(t_finfo *elem)
{
	printf("node:%p, %s\t", elem, elem->s_name);
	printf("%llu\n", elem->inf.st_ino);
}

void		ft_run_stacks(t_fstack *const restrict afil_stack,\
				const t_flags *const restrict aflags)
{
	finfo_lstiter(afil_stack->ndir_stack, &list_print);
	printf("now showing dir list\n");
	finfo_lstiter(afil_stack->dir_stack, &list_print);
	ft_fstack_del(afil_stack);
	(void)aflags;
}
