/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort_params.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 09:43:25 by aholster       #+#    #+#                */
/*   Updated: 2019/11/13 07:01:04 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	add_to_errqueue(const char *const restrict name,\
				t_fstack *const restrict afstack)
{
	t_list	*new;

	new = ft_lstnew(name, ft_strlen(name) + 1);
	if (new == NULL)
	{
		ft_error_cleanup(afstack);
	}
	else
	{
		ft_lstaddend(&(afstack->err_queue), new);
	}
}

static void	add_to_stack(const char *const restrict name,\
				const struct stat *const restrict stat_info,\
				t_fstack *const restrict afstack,\
				const t_flags aflags)
{
	t_finfo	*restrict	new_node;

	new_node = finfo_lstnew(name, stat_info);
	if (new_node == NULL)
	{
		ft_error_cleanup(afstack);
	}
	else
	{
		if ((aflags & flg_d) > 0 || S_ISDIR(new_node->stat.st_mode) != 1)
		{
			finfo_lstadd(&(afstack->ndir_stack), new_node);
		}
		else
		{
			finfo_lstadd(&(afstack->dir_stack), new_node);
		}
	}
}

void		ft_sort_params(char **restrict argv,\
				t_fstack *const restrict afstack,\
				const t_flags aflags)
{
	struct stat			stat_info;
	int					ret;

	while (argv[0] != NULL)
	{
		if ((aflags & flg_L) > 0)
		{
			ret = stat(argv[0], &stat_info);
		}
		else
		{
			ret = lstat(argv[0], &stat_info);
		}
		if (ret == 0)
		{
			add_to_stack(argv[0], &stat_info, afstack, aflags);
		}
		else
		{
			add_to_errqueue(argv[0], afstack);
		}
		argv++;
	}
}
