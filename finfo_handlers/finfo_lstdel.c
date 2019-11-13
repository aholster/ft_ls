/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_lstdel.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/22 17:40:24 by aholster       #+#    #+#                */
/*   Updated: 2019/11/13 02:52:11 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/finfo.h"

void	finfo_lstdel(t_finfo *restrict *const restrict alst)
{
	t_finfo *holder;
	t_finfo *current;

	if (alst == NULL || *alst == NULL)
	{
		return ;
	}
	else
	{
		current = *alst;
		*alst = NULL;
		while (current != NULL)
		{
			holder = current->next;
			finfo_lstdelone(&current);
			current = holder;
		}
	}
}
