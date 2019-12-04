/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_queue_push.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 20:54:16 by aholster       #+#    #+#                */
/*   Updated: 2019/12/04 12:47:02 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/finfo.h"

int			finfo_queue_push(\
				t_finfo_queue *const restrict aqueue,\
				const char *const restrict s_path,\
				const char *const restrict s_name,\
				const struct stat *const restrict astat_finfo)
{
	t_finfo	*new;

	new = finfo_lstnew(s_path, s_name, astat_finfo);
	if (new == NULL)
	{
		return (-1);
	}
	else
	{
		finfo_queue_add(aqueue, new);
		return (1);
	}
}
