/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort_params.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 09:43:25 by aholster       #+#    #+#                */
/*   Updated: 2019/12/01 02:27:46 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_ls.h"

static void	del_queues(t_fsort *const restrict afqueues)
{
	perror("ft_ls");
	finfo_lstdel(&(afqueues->ndir_queue.head));
	finfo_lstdel(&(afqueues->dir_queue.head));
	ft_lstdel(&(afqueues->err_queue.head), &ft_del);
	exit(-1);
}

static void	add_to_errqueue(const char *const restrict name,\
				t_fsort *const restrict afqueues)
{
	t_list	*new;

	new = ft_lstnew(name, ft_strlen(name) + 1);
	if (new == NULL)
	{
		del_queues(afqueues);
	}
	else
	{
		ft_lstqueue_add(&(afqueues->err_queue), new);
	}
}

static void	add_to_stack(const char *const restrict name,\
				const struct stat *const restrict stat_info,\
				t_fsort *const restrict afqueues,\
				const t_flags aflags)
{
	t_finfo	*restrict	new_node;

	new_node = finfo_lstnew(name, stat_info);
	if (new_node == NULL)
	{
		del_queues(afqueues);
	}
	else
	{
		if ((aflags & flg_d) > 0 || S_ISDIR(new_node->stat.st_mode) != 1)
		{
			finfo_lstadd(&(afqueues->ndir_queue), new_node);
		}
		else
		{
			finfo_lstadd(&(afqueues->dir_queue), new_node);
		}
	}
}

static void	iterate_arguments(char **restrict argv,\
				t_fsort *const restrict afqueues,\
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
			add_to_stack(argv[0], &stat_info, afqueues, aflags);
		}
		else
		{
			add_to_errqueue(argv[0], afqueues);
		}
		argv++;
	}
}

void		ft_sort_params(char **restrict argv,\
				t_fstack *const restrict afstack,\
				const t_flags aflags)
{
	t_fsort		sort_holder;

	ft_bzero(&sort_holder, sizeof(t_fsort));
	iterate_arguments(argv, &sort_holder, aflags);
	afstack->ndir_stack = sort_holder.ndir_queue.head;
	afstack->dir_stack = sort_holder.dir_queue.head;
	afstack->err_queue = sort_holder.err_queue.head;
}
