/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_lstiter.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/24 13:04:26 by aholster       #+#    #+#                */
/*   Updated: 2019/11/11 22:02:49 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/finfo.h"

void	finfo_lstiter(t_finfo *restrict lst,\
			void (*const f)(t_finfo *restrict elem))
{
	while (lst != NULL)
	{
		f(lst);
		lst = lst->next;
	}
}
