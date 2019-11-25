/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_lstnew.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 19:28:30 by aholster       #+#    #+#                */
/*   Updated: 2019/11/25 14:01:44 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/finfo.h"
#include "../libft/libft.h"

t_finfo	*finfo_lstnew(const char *const restrict s_name,
			const struct stat *const restrict astat_info)
{
	t_finfo	*restrict head;

	head = (t_finfo *)malloc(sizeof(t_finfo));
	if (head == NULL)
	{
		return (NULL);
	}
	else
	{
		ft_strcpy(head->s_name, s_name);
		// head->s_name = ft_strdup(s_name);
		// if (head->s_name == NULL)
		// {
		// 	free(head);
		// 	return (NULL);
		// }
	}
	ft_memcpy(&(head->stat), astat_info, sizeof(struct stat));
	head->next = NULL;
	head->fvect = NULL;
	return (head);
}
