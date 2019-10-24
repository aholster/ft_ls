/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lst_stack_pop.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/24 19:48:04 by aholster       #+#    #+#                */
/*   Updated: 2019/10/24 19:56:04 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_stack_pop(t_list **const astack)
{
	t_list *node;

	if (*astack == NULL)
	{
		return (NULL);
	}
	else
	{
		node = *astack;
		*astack = (*astack)->next;
		node->next = NULL;
		return (node);
	}
}
