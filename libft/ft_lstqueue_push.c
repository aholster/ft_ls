/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstqueue_push.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/20 09:03:43 by aholster       #+#    #+#                */
/*   Updated: 2019/11/20 09:10:07 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstqueue_push(t_queue *const aqueue,\
			void const *const content,\
			const size_t content_size)
{
	t_list	*new;

	new = ft_lstnew(content, content_size);
	if (new == NULL)
	{
		return (-1);
	}
	else
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
		return (1);
	}
}
