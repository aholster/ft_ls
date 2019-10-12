/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_run_stacks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/12 13:20:09 by aholster       #+#    #+#                */
/*   Updated: 2019/10/12 17:57:06 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <sys/stat.h>
static void	list_print(t_list *elem)
{
	struct stat	stat_s;

	lstat(elem->content, &stat_s);
	printf("node:%p, %s,\t", elem, elem->content);
	printf("%llu\n", stat_s.st_ino);
}

void		ft_run_stacks(t_list **const restrict andir_stack,\
				t_list **const restrict adir_stack,\
				const t_flags *const restrict aflags)
{
	ft_lstiter(*andir_stack, &list_print);
	ft_lstiter(*adir_stack, &list_print);
	ft_lstdel(andir_stack, &ft_del);
	ft_lstdel(adir_stack, &ft_del);
	(void)aflags;
}
