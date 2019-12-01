/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_lstdel.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/22 17:40:24 by aholster       #+#    #+#                */
/*   Updated: 2019/12/01 02:27:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/finfo.h"

void	finfo_lstdel(t_finfo **const restrict alst)
{
	t_finfo *holder;

	if (alst == NULL || *alst == NULL)
	{
		return ;
	}
	else
	{
		while (*alst != NULL)
		{
			holder = (*alst)->next;
			finfo_lstdelone(alst);
			*alst = holder;
		}
	}
}
