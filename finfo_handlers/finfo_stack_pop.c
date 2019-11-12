/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_stack_pop.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/24 19:03:23 by aholster       #+#    #+#                */
/*   Updated: 2019/11/11 22:02:49 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/finfo.h"

t_finfo	*finfo_stack_pop(t_finfo *restrict *const restrict afinfo_stack)
{
	t_finfo *pop;

	if (*afinfo_stack != NULL)
	{
		pop = *afinfo_stack;
		*afinfo_stack = (*afinfo_stack)->next;
		pop->next = NULL;
		return (pop);
	}
	else
	{
		return (NULL);
	}
}
