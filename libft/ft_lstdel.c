/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstdel.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/22 17:40:24 by aholster       #+#    #+#                */
/*   Updated: 2019/11/25 06:45:32 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **const alst,\
			void (*const del)(void *, size_t))
{
	t_list	*holder;
	t_list	*current;

	if (alst == NULL || *alst == NULL || del == NULL)
		return ;
	current = *alst;
	while (current != NULL)
	{
		holder = current->next;
		ft_lstdelone(&current, del);
		free(current);
		current = holder;
	}
	*alst = NULL;
}
