/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_dir_stack.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 16:34:08 by aholster       #+#    #+#                */
/*   Updated: 2019/10/31 00:10:34 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_stack_processors.h"

static void	list_print(t_finfo *elem)
{
	printf("node:%p, %s\n", elem, elem->s_name);
	// printf("time:%ld, %ld,\t%s\n", elem->stat.st_atimespec.tv_sec,\
	// 								elem->stat.st_atimespec.tv_nsec,\
	// 								elem->s_name);
//	printf("%llu\n", elem->stat.st_ino);
}

void	ft_process_dir_stack(t_fstack *const restrict afstack,\
			const t_flags *const restrict aflags)
{
	printf("now showing dir list\n");
	finfo_lstiter(afstack->dir_stack, &list_print);
	(void)aflags;
	(void)afstack;
}
