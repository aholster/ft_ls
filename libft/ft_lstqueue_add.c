/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstqueue_add.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/20 09:30:51 by aholster       #+#    #+#                */
/*   Updated: 2019/11/26 13:06:10 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstqueue_add(t_queue *const aqueue, t_list *const anode)
{
	if (aqueue->head == NULL)
	{
		aqueue->head = anode;
		aqueue->tail = anode;
	}
	else
	{
		aqueue->tail->next = anode;
		aqueue->tail = anode;
	}
}
