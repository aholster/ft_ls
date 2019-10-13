/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort_params.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 09:43:25 by aholster       #+#    #+#                */
/*   Updated: 2019/10/13 18:21:52 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <sys/stat.h>

static void	add_to_errstack(const char *const restrict name,\
				t_fstack *const restrict afstack)
{
	t_list	*new;

	new = ft_lstnew(name, ft_strlen(name));
	if (new == NULL)
	{
		ft_error_cleanup(afstack);
	}
	else
	{
		ft_lstadd(&(afstack->err_stack), new);
	}
}

static void	add_to_stack(const char *const restrict name,\
				const struct stat *const restrict stat_info,\
				t_fstack *const restrict afstack,\
				const t_flags *const restrict aflags)
{
	t_finfo	*restrict	new_node;

	new_node = finfo_lstnew(name, stat_info);
	if (new_node == NULL)
	{
		ft_error_cleanup(afstack);
	}
	else
	{
		if (((*aflags) & flg_d) == 1 || S_ISDIR(new_node->inf.st_mode) != 1)
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
				const t_flags *const restrict aflags)
{
	struct stat			stat_info;
	int					ret;

	while (argv[0] != NULL)
	{
		ret = lstat(argv[0], &stat_info);
		if (ret == 0)
		{
			add_to_stack(argv[0], &stat_info, afstack, aflags);
		}
		else
		{
			add_to_errstack(argv[0], afstack);
		}
		argv++;
	}
}
