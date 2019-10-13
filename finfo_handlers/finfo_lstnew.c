/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_lstnew.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 19:28:30 by aholster       #+#    #+#                */
/*   Updated: 2019/10/13 13:30:36 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/finfo.h"
#include "./../libft/libft.h"

t_finfo	*finfo_lstnew(const char *const restrict s_name,
			const struct stat *const restrict astat_info)
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
	ft_memcpy(&(head->inf), astat_info, sizeof(struct stat));
	head->next = NULL;
	return (head);
}
