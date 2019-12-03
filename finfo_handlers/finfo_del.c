/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_del.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/22 17:40:24 by aholster       #+#    #+#                */
/*   Updated: 2019/12/03 09:04:33 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/finfo.h"
#include "../libft/libft.h"

void	finfo_del(t_finfo_queue *const restrict aqueue)
{
	t_finfo *holder;
	t_finfo *iter;

	iter = aqueue->head;
	while (iter != NULL)
	{
		holder = iter->next;
		finfo_lstdelone(&iter);
		iter = holder;
	}
	ft_bzero(aqueue, sizeof(t_finfo_queue));
}
