/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstqueue_pop.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/20 09:03:41 by aholster       #+#    #+#                */
/*   Updated: 2019/11/26 13:08:43 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstqueue_pop(t_queue *const aqueue)
{
	t_list *const	head = aqueue->head;

	if (head != NULL)
	{
		if (head == aqueue->tail)
		{
			aqueue->tail = NULL;
			aqueue->head = NULL;
			return (head);
		}
		else
		{
			aqueue->head = head->next;
			return (head);
		}
	}
	else
	{
		return (NULL);
	}
}
