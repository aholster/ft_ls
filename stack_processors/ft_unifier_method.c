/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_unifier_method.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 21:53:46 by aholster       #+#    #+#                */
/*   Updated: 2019/11/18 22:46:01 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"
#include <limits.h>

static int	unify_l_i(const t_fvec *const restrict components,\
				t_compcaps *const restrict acaps,\
				t_list **const restrict aproduct_stack)
{
	int		status;
	char	*output;

	status = asprintf(&output, "%*s %s%*s %-*s %-*s %*s %s %s",\
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
		return (-1);
	}
	else if (ft_lst_stack_push(aproduct_stack, output, status + 1) == -1)
	{
		free(output);
		return (-1);
	}
	return (status);
}

static int	unify_l(const t_fvec *const restrict components,\
				t_compcaps *const restrict acaps,\
				t_list **const restrict aproduct_stack)
{
	int		status;
	char	*output;

	status = asprintf(&output, "%s%*s %-*s %-*s %*s %s %s",\
			components->svec + components->indices[f_perm],\
			acaps->hlink_len, components->svec + components->indices[f_nlnk],\
			acaps->uname_len, components->svec + components->indices[f_uid],\
			acaps->gname_len, components->svec + components->indices[f_gid],\
			acaps->fsize_len, components->svec + components->indices[f_size],\
			components->svec + components->indices[f_date],\
			components->svec + components->indices[f_name]);
	if (status < 0)
	{
		return (-1);
	}
	else if (ft_lst_stack_push(aproduct_stack, output, status + 1) == -1)
	{
		free(output);
		return (-1);
	}
	return (status);
}

static int	unify_i(const t_fvec *const restrict components,\
				t_compcaps *const restrict acaps,\
				t_list **const restrict aproduct_stack)
{
	int		status;
	char	*output;

	status = asprintf(&output, "%*s %s", acaps->inode_len,\
			components->svec + components->indices[f_inode],\
			components->svec + components->indices[f_name]);
	if (status <= 0)
	{
		return (-1);
	}
	else if (ft_lst_stack_push(aproduct_stack, output, status + 1) == -1)
	{
		free(output);
		return (-1);
	}
	return (status);
}

static int	unify_basic(const t_fvec *const restrict components,\
				t_compcaps *const restrict acaps,\
				t_list **const restrict aproduct_stack)
{
	int		status;
	char	buf[PATH_MAX + 1];

	status = snprintf(buf, sizeof(buf), "%s",\
			components->svec + components->indices[f_name]);
	if (status <= 0)
	{
		return (-1);
	}
	else if (ft_lst_stack_push(aproduct_stack, buf, status + 1) == -1)
	{
		return (-1);
	}
	(void)acaps;
	return (status);
}

t_unifier	ft_unifier_method(const t_flags aflags)
{
	if ((aflags & (flg_l | flg_i)) > 0)
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

