/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_lstnew.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 19:28:30 by aholster       #+#    #+#                */
/*   Updated: 2019/11/26 12:40:45 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/finfo.h"
#include "../libft/libft.h"

t_finfo	*finfo_lstnew(const char *const restrict s_name,\
			const struct stat *const restrict astat_info)
{
	t_finfo	*restrict	new;
	size_t				name_len;

	new = (t_finfo *)ft_calloc(sizeof(t_finfo), 1);
	if (new == NULL)
	{
		return (NULL);
	}
	else
	{
		name_len = ft_strlen(s_name);
		ft_memcpy(new->s_name, s_name, name_len + 1);
		new->s_namelen = name_len + 1;
		ft_memcpy(&(new->stat), astat_info, sizeof(struct stat));
		return (new);
	}
}
