/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_lstadd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 19:28:11 by aholster       #+#    #+#                */
/*   Updated: 2019/12/01 02:09:26 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/finfo.h"

void	finfo_lstadd(t_finfo_queue *const restrict aqueue,\
			t_finfo *const new)
{
	if (aqueue->head == NULL)
	{
		aqueue->head = new;
		aqueue->tail = new;
	}
	else
	{
		aqueue->tail->next = new;
		aqueue->tail = new;
	}
}
