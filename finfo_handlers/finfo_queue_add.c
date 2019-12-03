/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_queue_add.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 19:28:11 by aholster       #+#    #+#                */
/*   Updated: 2019/12/03 05:28:02 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/finfo.h"

void	finfo_queue_add(t_finfo_queue *const restrict aqueue,\
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
