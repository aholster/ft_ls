/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_lstaddend.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 10:18:57 by aholster       #+#    #+#                */
/*   Updated: 2019/10/14 10:23:41 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/finfo.h"

t_finfo	*finfo_lstaddend(t_finfo *restrict *const restrict lst,\
						t_finfo *const new)
{
	t_finfo *internal;

	if (*lst == NULL)
	{
		*lst = new;
		return (new);
	}
	internal = *lst;
	while (internal->next != NULL)
	{
		internal = internal->next;
	}
	internal->next = new;
	return (new);
}
