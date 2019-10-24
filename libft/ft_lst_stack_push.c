/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lst_stack_push.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/24 19:48:06 by aholster       #+#    #+#                */
/*   Updated: 2019/10/24 19:51:01 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lst_stack_push(t_list **const astack,\
		void const *content,\
		const size_t content_size)
{
	t_list *node;

	node = ft_lstnew(content, content_size);
	if (node == NULL)
	{
		return (-1);
	}
	else
	{
		ft_lstadd(astack, node);
		return (1);
	}
}
