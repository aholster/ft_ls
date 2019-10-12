/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_lstdel.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/22 17:40:24 by aholster       #+#    #+#                */
/*   Updated: 2019/10/12 19:14:41 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_finfo.h"

void	finfo_lstdel(t_finfo *restrict *const restrict alst)
{
	t_finfo *holder;
	t_finfo *current;

	if (alst == NULL || *alst == NULL)
		return ;
	current = *alst;
	*alst = NULL;
	while (current != NULL)
	{
		holder = current->next;
		finfo_lstdelone(&current);
		current = holder;
	}
}
