/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo_lstnew.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/21 19:28:30 by aholster       #+#    #+#                */
/*   Updated: 2019/12/04 17:25:29 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/finfo.h"
#include "../libft/libft.h"

static void	enter_names(const char *const restrict s_path,\
				const char *const restrict s_name,\
				t_finfo *const restrict new)
{
	if (new->s_pathlen != 0)
	{
		ft_memcpy(new->s_path, s_path, new->s_pathlen);
		new->s_path[new->s_pathlen] = '/';
		new->s_pathlen += 1;
	}
	new->s_name = new->s_path + new->s_pathlen;
	ft_memcpy(new->s_name, s_name, new->s_namelen);
}

t_finfo		*finfo_lstnew(const char *const restrict s_path,\
				const char *const restrict s_name,\
				const struct stat *const restrict astat_info)
{
	t_finfo	*restrict	new;

	new = (t_finfo *)ft_calloc(sizeof(t_finfo), 1);
	if (new == NULL)
	{
		return (NULL);
	}
	else
	{
		new->s_pathlen = ft_strlen(s_path);
		new->s_namelen = ft_strlen(s_name) + 1;
		if (new->s_namelen + new->s_pathlen + 1 > sizeof(new->s_path))
		{
			free(new);
			return (NULL);
		}
		else
		{
			enter_names(s_path, s_name, new);
			ft_memcpy(&(new->stat), astat_info, sizeof(struct stat));
			return (new);
		}
	}
}
