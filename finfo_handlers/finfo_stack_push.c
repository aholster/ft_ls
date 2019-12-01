/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_stack_push.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 20:54:16 by aholster       #+#    #+#                */
/*   Updated: 2019/12/01 02:33:51 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/finfo.h"

int			finfo_stack_push(\
				t_finfo *restrict *const restrict afinfo_stack,\
				const char *const restrict s_name,\
				const struct stat *const restrict astat_finfo)
{
	t_finfo	*new;

	new = finfo_lstnew(s_name, astat_finfo);
	if (new == NULL)
	{
		return (-1);
	}
	else
	{
		new->next = *afinfo_stack;
		*afinfo_stack = new;
		return (1);
	}
}
