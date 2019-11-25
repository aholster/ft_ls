/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unifier_method.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 21:53:46 by aholster       #+#    #+#                */
/*   Updated: 2019/11/25 09:12:42 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"

static t_list	*unify_l_i(const t_fvec *const restrict components,\
					const t_compcaps *const restrict acaps)
{
	int		status;
	char	*str;
	t_list	*new;

	status = asprintf(&str, "%*s %s%*s %-*s %-*s %*s %s %s",\
			acaps->inode_len, components->svec + components->indices[f_inode],\
			components->svec + components->indices[f_perm],\
			acaps->hlink_len, components->svec + components->indices[f_nlnk],\
			acaps->uname_len, components->svec + components->indices[f_uid],\
			acaps->gname_len, components->svec + components->indices[f_gid],\
			acaps->fsize_len, components->svec + components->indices[f_size],\
			components->svec + components->indices[f_date],\
			components->svec + components->indices[f_name]);
	if (status < 0)
	{
		return (NULL);
	}
	else
	{
		new = ft_lstnew(str, status + 1);
		free(str);
	}
	return (new);
}

static t_list	*unify_l(const t_fvec *const restrict components,\
					const t_compcaps *const restrict acaps)
{
	int		status;
	char	*str;
	t_list	*new;

	status = asprintf(&str, "%s%*s %-*s %-*s %*s %s %s",\
			components->svec + components->indices[f_perm],\
			acaps->hlink_len, components->svec + components->indices[f_nlnk],\
			acaps->uname_len, components->svec + components->indices[f_uid],\
			acaps->gname_len, components->svec + components->indices[f_gid],\
			acaps->fsize_len, components->svec + components->indices[f_size],\
			components->svec + components->indices[f_date],\
			components->svec + components->indices[f_name]);
	if (status < 0)
	{
		return (NULL);
	}
	else
	{
		new = ft_lstnew(str, status + 1);
		free(str);
	}
	return (new);
}

static t_list	*unify_i(const t_fvec *const restrict components,\
					const t_compcaps *const restrict acaps)
{
	int		status;
	char	str[MAX_NAMELEN + 25 + 1];
	t_list	*new;

	status = snprintf(str, sizeof(str), "%*s %s", acaps->inode_len,\
			components->svec + components->indices[f_inode],\
			components->svec + components->indices[f_name]);
	if (status <= 0)
	{
		return (NULL);
	}
	else
	{
		new = ft_lstnew(str, status + 1);
	}
	return (new);
}

static t_list	*unify_basic(const t_fvec *const restrict components,\
					const t_compcaps *const restrict acaps)
{
	int		status;
	char	str[MAX_NAMELEN + 1];
	t_list	*new;

	status = snprintf(str, sizeof(str), "%s",\
			components->svec + components->indices[f_name]);
	if (status <= 0)
	{
		return (NULL);
	}
	else
	{
		new = ft_lstnew(str, status + 1);
	}
	(void)acaps;
	return (new);
}

t_unifier		ft_unifier_method(const t_flags aflags)
{
	if ((aflags & (flg_l | flg_i)) == (flg_l | flg_i))
	{
		return (&unify_l_i);
	}
	else if ((aflags & flg_l) > 0)
	{
		return (&unify_l);
	}
	else if ((aflags & flg_i) > 0)
	{
		return (&unify_i);
	}
	else
	{
		return (&unify_basic);
	}
}
