/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_lstnew.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 19:28:30 by aholster       #+#    #+#                */
/*   Updated: 2019/10/12 17:55:25 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_finfo.h"
#include "./../libft/libft.h"

t_finfo	*finfo_lstnew(const char *const restrict s_name)
{
	t_finfo	*restrict head;

	head = (t_finfo *)malloc(sizeof(t_finfo));
	if (head == NULL)
		return (NULL);
	else
	{
		head->s_name = ft_strdup(s_name);
		if (head->s_name == NULL)
		{
			free(head);
			return (NULL);
		}
	}
	head->next = NULL;
	return (head);
}
