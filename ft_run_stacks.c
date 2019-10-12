/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_run_stacks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/12 13:20:09 by aholster       #+#    #+#                */
/*   Updated: 2019/10/12 19:09:34 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <sys/stat.h>

//#include "./incl/ft_finfo.h"
static void	list_print(t_finfo *elem)
{
	struct stat	stat_s;

	lstat(elem->s_name, &stat_s);
	printf("node:%p, %s,\t", elem, elem->s_name);
	printf("%llu\n", stat_s.st_ino);
}

void		ft_run_stacks(t_finfo *restrict *const restrict andir_stack,\
				t_finfo *restrict *const restrict adir_stack,\
				const t_flags *const restrict aflags)
{
	finfo_lstiter(*andir_stack, &list_print);
	finfo_lstiter(*adir_stack, &list_print);
	finfo_lstdel(andir_stack);
	finfo_lstdel(adir_stack);
	(void)aflags;
}
